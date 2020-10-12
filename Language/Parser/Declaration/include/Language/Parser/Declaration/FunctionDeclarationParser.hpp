#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Function/FunctionDeclaration.hpp>
#include <Language/Parser/Instruction/InstructionParser.hpp>

namespace Language::Parser::Declaration
{
	inline std::unique_ptr<AST::Core::Instruction> parseFunctionDeclaration(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt(AST::Function::FunctionDeclaration::Keyword))
			return nullptr;
		context.skipSpacesAndComments();

		auto functionName = cursor.getKeywordRequired("Le mot clef function doit etre suivi d un nom de fonction.");
		if (cursor.getChar() != '(')
			throw std::runtime_error{"La declaration d une fonction doit avoir des parentheses."};
		++cursor.pos;

		auto functionDeclaration = std::make_unique<AST::Function::FunctionDeclaration>(std::move(functionName), &scope);
		auto functionStatementParserInformations = AST::ParsingTools::Context{*functionDeclaration, *functionDeclaration, cursor, verbose};
		if (verbose)
			CppUtils::Log::Logger::logInformation(AST::Function::FunctionDeclaration::Keyword.data() + " "s + functionDeclaration->getName().data() + '(', false);
		context.skipSpacesAndComments();
		if (cursor.getChar() != ')')
		{
			auto loop = true;
			do
			{
				auto keyword = cursor.getKeywordRequired("Le mot clef let ou const est attendu.");
				if (keyword != "let" && keyword != "const")
					throw std::runtime_error{"Le mot clef let ou const est attendu."};
				const auto constant = (keyword == "const");
				context.skipSpacesAndComments();
				auto argumentName = cursor.getKeywordRequired("Le mot clef " + keyword + " doit etre suivi d'un nom de variable.");
				context.skipSpacesAndComments();
				if (cursor.getChar() != ':')
					throw std::runtime_error{"Le type de l argument doit etre renseigne."};
				++cursor.pos;
				context.skipSpacesAndComments();
				auto typeName = cursor.getKeywordRequired("Le nom d'un type est attendu.");
				
				if (verbose)
					CppUtils::Log::Logger::logInformation(keyword + " " + argumentName + ": " + typeName, false);
				auto argumentType = CppUtils::Type::TypeId{typeName};
				argumentType.saveTypename();
				functionDeclaration->addArgument(AST::Variable::VariableSignature{std::move(argumentName), constant, std::move(argumentType)});
				
				context.skipSpacesAndComments();
				loop = (cursor.getChar() == ',');
				if (loop)
				{
					if (verbose)
						CppUtils::Log::Logger::logInformation(", ", false);
					++cursor.pos;
				}
				context.skipSpacesAndComments();
			}
			while (loop);
			if (cursor.getChar() != ')')
				throw std::runtime_error{"Vous avez probablement oublie de fermer les parentheses d une fonction."};
		}
		++cursor.pos;
		if (verbose)
			CppUtils::Log::Logger::logInformation(")", false);

		context.skipSpacesAndComments();
		if (cursor.getChar() == ':')
		{
			++cursor.pos;
			context.skipSpacesAndComments();
			auto typeName = cursor.getKeywordRequired("Le nom d'un type est attendu.");
			if (verbose)
				CppUtils::Log::Logger::logInformation(": " + typeName);
			auto returnType = CppUtils::Type::TypeId{typeName};
			returnType.saveTypename();
			functionDeclaration->setReturnType(std::move(returnType));
		}
		else
		{
			if (verbose)
				CppUtils::Log::Logger::logInformation("");
			functionDeclaration->setReturnType(AST::Type::Void::TypeId);
		}
		
		auto instruction = Instruction::parseInstruction(functionStatementParserInformations);
		if (!instruction)
			throw std::runtime_error{"Une instruction est requise dans la declaration de la fonction."};
		functionDeclaration->addInstruction(std::move(instruction));
		
		return functionDeclaration;
	}
}
