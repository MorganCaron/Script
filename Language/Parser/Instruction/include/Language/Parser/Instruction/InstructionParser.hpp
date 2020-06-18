#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseInstruction(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos] = cursor;

		cursor.skipSpaces();
		const auto& parserScope = dynamic_cast<const AST::ParsingTools::ParserScope&>(scope.findScope(AST::ParsingTools::ParserScopeType));
		const auto& instructionParsers = parserScope.getInstructionParsers();
		for (const auto& instructionParser : instructionParsers)
		{
			auto startPos = pos;
			auto instruction = instructionParser.second(cursor);
			if (instruction)
			{
				if (!cursor.isEndOfCode() && cursor.getChar() == ';')
					++pos;
				CppUtils::Logger::logDebug(" -> " + instructionParser.first + " parser: " + instruction->getInstructionType());
				return instruction;
			}
			pos = startPos;
		}
		return nullptr;
	}
}
