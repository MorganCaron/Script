#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Instruction/Bracket.hpp>
#include <Language/Parser/Instruction/InstructionParser.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseBracket(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos] = cursor;

		if (cursor.getChar() != '{')
			return nullptr;
		
		auto bracket = std::make_unique<AST::Instruction::Bracket>(&scope);
		auto bracketParsingInformations = AST::ParsingTools::Cursor{*bracket, *bracket, src, ++pos};
		CppUtils::Logger::logInformation("{");
		
		while (!cursor.isEndOfCode() && cursor.getChar() != '}')
		{
			auto instruction = parseInstruction(bracketParsingInformations);
			cursor.skipSpaces();
			if (instruction != nullptr)
				bracket->addInstruction(std::move(instruction));
			else if (cursor.getChar() != '}')
				throw std::runtime_error{"Erreur de syntaxe. La chaine ne correspond a aucune instruction connue."};
		}
		if (cursor.isEndOfCode())
			throw std::runtime_error{"Une accolade n est jamais fermee."};
		++pos;
		CppUtils::Logger::logInformation("}", false);

		return bracket;
	}
}
