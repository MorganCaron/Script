#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>

namespace Language::Parser::Declaration
{
	inline std::unique_ptr<AST::Core::Instruction> parseDeclaration(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos, verbose] = cursor;

		cursor.skipSpaces();
		if (cursor.isEndOfCode())
			return nullptr;
		
		const auto& parserScope = dynamic_cast<const AST::ParsingTools::ParserScope&>(scope.findScope(AST::ParsingTools::ParserScopeType));
		const auto& declarationParsers = parserScope.getDeclarationParsers();
		for (const auto& [parserName, parserFunction] : declarationParsers)
		{
			auto startPos = pos;
			try
			{
				auto declaration = parserFunction(cursor);
				if (declaration)
				{
					if (verbose)
						CppUtils::Log::Logger::logDebug(" -> "s + declaration->getInstructionType().name.data());
					return declaration;
				}
				pos = startPos;
			}
			catch (const std::exception& error)
			{
				pos = startPos;
				throw std::runtime_error{"In "s + parserName + ":\n" + error.what()};
			}
		}
		throw std::runtime_error{"Erreur de syntaxe. La chaine suivante ne correspond a aucune declaration connue:\n" + cursor.getNextNChar(20) + "..."};
		return nullptr;
	}
}
