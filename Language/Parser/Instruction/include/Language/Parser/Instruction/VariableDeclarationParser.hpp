#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Type/Type.hpp>
#include <Language/AST/Variable/VariableDeclaration.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseVariableDeclaration(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos] = cursor;

		auto keyword = cursor.getWordAndSkipIt();
		if (keyword != "let" && keyword != "const")
			return nullptr;

		const auto constant = (keyword == "const");
		cursor.skipSpaces();
		auto variableName = cursor.getWordRequired("Le mot clef " + keyword + " doit etre suivi d'un nom de variable.");
		cursor.skipSpaces();
		
		CppUtils::Logger::logInformation(keyword + " " + variableName, false);

		auto typeName = std::string{};
		const auto typed = (cursor.getChar() == ':');
		if (typed)
		{
			++pos;
			cursor.skipSpaces();
			auto typeName = cursor.getWordRequired("Le nom d'un type est attendu.");
			CppUtils::Logger::logInformation(": " + typeName, false);
		}

		cursor.skipSpaces();
		auto value = std::unique_ptr<AST::Type::IValue>(nullptr);
		if (cursor.getChar() == '=')
		{
			++pos;
			CppUtils::Logger::logInformation(" = ", false);
			cursor.skipSpaces();
			auto valueInstruction = Value::parseValue(cursor);
			if (valueInstruction == nullptr)
				throw std::runtime_error{"Une valeur est attendue."};
			value = valueInstruction->interpret();
			if (typed && !value->isType(CppUtils::Hash::constexprHash(typeName)))
				throw std::runtime_error{"La valeur ne correspond pas au type de la variable."};
		}

		typeName = typed ? typeName : value->getTypeName().data();
		return std::make_unique<AST::Variable::VariableDeclaration>(std::move(variableName), &scope, constant, std::move(value), typeName);
	}
}
