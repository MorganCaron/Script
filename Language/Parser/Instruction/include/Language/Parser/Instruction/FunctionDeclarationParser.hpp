#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Function/FunctionDeclaration.hpp>
#include <Language/Parser/Instruction/InstructionParser.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseFunctionDeclaration(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos] = cursor;

		if (!cursor.isKeywordSkipIt(AST::Function::FunctionDeclaration::Keyword))
			return nullptr;
		cursor.skipSpaces();

		auto functionName = cursor.getWordRequired("Le mot clef function doit etre suivi d un nom de fonction.");
		if (src.at(pos) != '(')
			throw std::runtime_error{"La declaration d une fonction doit avoir des parentheses."};
		++pos;

		auto functionDeclaration = std::make_unique<AST::Function::FunctionDeclaration>(std::move(functionName), &scope);
		auto functionStatementParserInformations = AST::ParsingTools::Cursor{*functionDeclaration, *functionDeclaration, src, pos};
		CppUtils::Logger::logInformation(AST::Function::FunctionDeclaration::Keyword.data() + " "s + functionDeclaration->getName().data() + '(', false);
		cursor.skipSpaces();
		if (cursor.getChar() != ')')
		{
			auto loop = true;
			do
			{
				auto keyword = cursor.getWordRequired("Le mot clef let ou const est attendu.");
				const auto constant = (keyword == "const");
				cursor.skipSpaces();
				auto argumentName = cursor.getWordRequired("Le mot clef " + keyword + " doit etre suivi d'un nom de variable.");
				cursor.skipSpaces();
				if (cursor.getChar() != ':')
					throw std::runtime_error{"Le type de l argument doit etre renseigne."};
				++pos;
				cursor.skipSpaces();
				auto typeName = cursor.getWordRequired("Le nom d'un type est attendu.");
				
				CppUtils::Logger::logInformation(keyword + " " + argumentName + ": " + typeName, false);
				auto signature = AST::Variable::VariableScope::VariableSignature{constant, std::move(typeName)};
				functionDeclaration->addArgument(std::move(argumentName), std::move(signature));
				
				cursor.skipSpaces();
				loop = (cursor.getChar() == ',');
				if (loop)
				{
					CppUtils::Logger::logInformation(", ", false);
					++pos;
				}
				cursor.skipSpaces();
			}
			while (loop);
			if (cursor.getChar() != ')')
				throw std::runtime_error{"Vous avez probablement oublie de fermer les parentheses d une fonction."};
		}
		++cursor.pos;
		CppUtils::Logger::logInformation(")");
		
		auto instruction = parseInstruction(functionStatementParserInformations);
		if (!instruction)
			throw std::runtime_error{"Une instruction est requise dans la declaration de la fonction."};
		functionDeclaration->addInstruction(std::move(instruction));
		return functionDeclaration;
	}
}
