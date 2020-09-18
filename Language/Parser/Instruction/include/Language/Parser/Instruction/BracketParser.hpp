#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Instruction/Bracket.hpp>
#include <Language/Parser/Instruction/InstructionParser.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseBracket(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos, verbose] = cursor;

		if (cursor.getChar() != '{')
			return nullptr;
		if (verbose)
			CppUtils::Log::Logger::logInformation("{");
		
		auto bracket = std::make_unique<AST::Instruction::Bracket>(&scope);
		auto bracketParsingInformations = AST::ParsingTools::Cursor{*bracket, *bracket, src, ++pos, verbose};
		
		while (!cursor.isEndOfCode() && cursor.getChar() != '}')
		{
			bracket->addInstruction(parseInstruction(bracketParsingInformations));
			cursor.skipSpaces();
		}
		if (cursor.isEndOfCode())
			throw std::runtime_error{"Une accolade n est jamais fermee."};
		if (verbose)
			CppUtils::Log::Logger::logInformation("}", false);
		++pos;

		if (bracket->getNbInstructions() == 0)
			CppUtils::Log::Logger::logWarning("Les accolades vides sont inutiles. Il semblerait que vous avez oublie quelque chose ou que votre code peut s ecrire plus proprement.");
		if (bracket->getNbInstructions() == 1)
			CppUtils::Log::Logger::logWarning("Les accolades sont inutiles lorsqu elles ne contiennent qu une seule instruction.");

		return bracket;
	}
}
