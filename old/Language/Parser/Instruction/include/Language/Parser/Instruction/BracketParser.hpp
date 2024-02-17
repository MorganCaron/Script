#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Instruction/Bracket.hpp>
#include <Language/Parser/Instruction/InstructionParser.hpp>

namespace Script::Language::Parser::Instruction
{
	std::unique_ptr<AST::Core::Instruction> parseBracket(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (cursor.getChar() != '{')
			return nullptr;
		if (verbose)
			CppUtils::Log::Logger::logInformation("{");
		
		auto bracket = std::make_unique<AST::Instruction::Bracket>(&scope);
		++cursor.pos;
		auto bracketParsingInformations = AST::ParsingTools::Context{*bracket, *bracket, cursor, verbose};
		
		while (!cursor.isEndOfString() && cursor.getChar() != '}')
		{
			bracket->addInstruction(parseInstruction(bracketParsingInformations));
			context.skipSpacesAndComments();
		}
		if (cursor.isEndOfString())
			throw std::runtime_error{"Une accolade n est jamais fermee."};
		if (verbose)
			CppUtils::Log::Logger::logInformation("}", false);
		++cursor.pos;

		if (bracket->getNbInstructions() == 0)
			CppUtils::Log::Logger::logWarning("Les accolades vides sont inutiles. Il semblerait que vous avez oublie quelque chose ou que votre code peut s ecrire plus proprement.");
		return bracket;
	}
}
