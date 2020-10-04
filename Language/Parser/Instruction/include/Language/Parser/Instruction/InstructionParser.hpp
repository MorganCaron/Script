#pragma once

#include <Language/AST/ParsingTools/Context.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseInstruction(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		context.skipSpacesAndComments();
		if (cursor.isEndOfString())
			return nullptr;
		
		const auto& parserScope = dynamic_cast<const AST::ParsingTools::ParserScope&>(scope.findScope(AST::ParsingTools::ParserScopeType));
		const auto& instructionParsers = parserScope.getInstructionParsers();
		for (const auto& [parserName, parserFunction] : instructionParsers)
		{
			auto startPos = cursor.pos;
			try
			{
				auto instruction = parserFunction(context);
				if (instruction)
				{
					if (verbose)
						CppUtils::Log::Logger::logDebug(" -> "s + instruction->getInstructionType().name.data());
					return instruction;
				}
				cursor.pos = startPos;
			}
			catch (const std::exception& error)
			{
				cursor.pos = startPos;
				throw std::runtime_error{"In "s + parserName + ":\n" + error.what()};
			}
		}

		throw std::runtime_error{"Erreur de syntaxe. La chaine suivante ne correspond a aucune instruction connue:\n" + std::string{CppUtils::String::trimString(cursor.getNextNChar(20))} + "..."};
		return nullptr;
	}
}
