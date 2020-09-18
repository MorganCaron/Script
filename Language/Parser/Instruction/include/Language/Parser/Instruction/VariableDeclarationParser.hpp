#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Type/Type.hpp>
#include <Language/AST/Variable/VariableDeclaration.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseVariableDeclaration(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos, verbose] = cursor;

		auto keyword = cursor.getWordAndSkipIt();
		if (keyword != "let" && keyword != "const")
			return nullptr;

		const auto constant = (keyword == "const");
		cursor.skipSpaces();
		auto variableName = cursor.getWordRequired("Le mot clef " + keyword + " doit etre suivi d'un nom de variable.");
		cursor.skipSpaces();
		
		if (verbose)
			CppUtils::Log::Logger::logInformation(keyword + " " + variableName, false);

		const auto typed = (cursor.getChar() == ':');
		auto type = CppUtils::Type::TypeId{};
		auto typeName = std::string{};
		if (typed)
		{
			++pos;
			cursor.skipSpaces();
			typeName = cursor.getWordRequired("Le nom d'un type est attendu.");
			if (verbose)
			{
				CppUtils::Log::Logger::logInformation(": ", false);
				CppUtils::Log::Logger::logDetail(typeName, false);
			}
			type = CppUtils::Type::TypeId{typeName};
		}

		cursor.skipSpaces();
		if (cursor.getChar() == '=')
		{
			++pos;
			if (verbose)
				CppUtils::Log::Logger::logInformation(" = ", false);
			cursor.skipSpaces();
			auto valueInstruction = Value::parseValue(cursor);
			if (valueInstruction == nullptr)
				throw std::runtime_error{"Une valeur est attendue."};
			const auto returnType = valueInstruction->getReturnType();
			if (typed && type != returnType)
				throw std::runtime_error{"La valeur ne correspond pas au type de la variable."};
			cursor.parseSemicolon();
			auto variableDeclaration = std::make_unique<AST::Variable::VariableDeclaration>(&scope, AST::Variable::VariableSignature{std::move(variableName), constant, std::move(returnType)});
			variableDeclaration->addInstruction(std::move(valueInstruction));
			return variableDeclaration;
		}

		if (!typed)
			throw std::runtime_error{"Une variable declaree sans valeur doit etre explicitement typee."};
		cursor.parseSemicolon();
		auto variableType = CppUtils::Type::TypeId{typeName};
		variableType.saveTypename();
		return std::make_unique<AST::Variable::VariableDeclaration>(&scope, AST::Variable::VariableSignature{std::move(variableName), constant, std::move(variableType)});
	}
}
