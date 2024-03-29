#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Type/Type.hpp>
#include <Language/AST/Variable/VariableDeclaration.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Script::Language::Parser::Instruction
{
	std::unique_ptr<AST::Core::Instruction> parseVariableDeclaration(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		auto keyword = cursor.getKeywordAndSkipIt();
		if (keyword != "let" && keyword != "const")
			return nullptr;

		const auto constant = (keyword == "const");
		context.skipSpacesAndComments();
		auto variableName = std::string{cursor.getKeywordRequired("Le mot clef " + std::string{keyword} + " doit etre suivi d'un nom de variable.")};
		context.skipSpacesAndComments();
		
		if (verbose)
			CppUtils::Log::Logger::logInformation(std::string{keyword} + " " + variableName, false);

		const auto typed = (cursor.getChar() == ':');
		auto type = CppUtils::Type::Token{};
		auto typeName = std::string{};
		if (typed)
		{
			++cursor.pos;
			context.skipSpacesAndComments();
			typeName = cursor.getKeywordRequired("Le nom d'un type est attendu.");
			if (verbose)
			{
				CppUtils::Log::Logger::logInformation(": ", false);
				CppUtils::Log::Logger::logDetail(typeName, false);
			}
			type = CppUtils::Type::Token{typeName};
		}

		context.skipSpacesAndComments();
		if (cursor.getChar() == '=')
		{
			++cursor.pos;
			if (verbose)
				CppUtils::Log::Logger::logInformation(" = ", false);
			context.skipSpacesAndComments();
			auto valueInstruction = Value::parseOperation(context);
			if (valueInstruction == nullptr)
				throw std::runtime_error{"Une valeur est attendue."};
			const auto returnType = valueInstruction->getReturnType();
			if (typed && type != returnType)
				throw std::runtime_error{"La valeur ne correspond pas au type de la variable."};
			context.parseSemicolon();
			auto variableDeclaration = std::make_unique<AST::Variable::VariableDeclaration>(&scope, AST::Variable::VariableSignature{std::move(variableName), constant, std::move(returnType)});
			variableDeclaration->addInstruction(std::move(valueInstruction));
			return variableDeclaration;
		}

		if (!typed)
			throw std::runtime_error{"Une variable declaree sans valeur doit etre explicitement typee."};
		context.parseSemicolon();
		auto variableType = CppUtils::Type::Token{typeName};
		variableType.saveTypename();
		return std::make_unique<AST::Variable::VariableDeclaration>(&scope, AST::Variable::VariableSignature{std::move(variableName), constant, std::move(variableType)});
	}
}
