#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseInstruction(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos, verbose] = cursor;

		cursor.skipSpaces();
		if (cursor.isEndOfCode())
			return nullptr;
		
		const auto& parserScope = dynamic_cast<const AST::ParsingTools::ParserScope&>(scope.findScope(AST::ParsingTools::ParserScopeType));
		const auto& instructionParsers = parserScope.getInstructionParsers();
		for (const auto& [parserName, parserFunction] : instructionParsers)
		{
			auto startPos = pos;
			try
			{
				auto instruction = parserFunction(cursor);
				if (instruction)
				{
					if (verbose)
						CppUtils::Log::Logger::logDebug(" -> "s + instruction->getInstructionType().name.data());
					return instruction;
				}
				pos = startPos;
			}
			catch (const std::exception& error)
			{
				pos = startPos;
				throw std::runtime_error{"In "s + parserName + ":\n" + error.what()};
			}
		}

		throw std::runtime_error{"Erreur de syntaxe. La chaine suivante ne correspond a aucune instruction connue:\n" + cursor.getNextNChar(20) + "..."};
		return nullptr;
	}
}
