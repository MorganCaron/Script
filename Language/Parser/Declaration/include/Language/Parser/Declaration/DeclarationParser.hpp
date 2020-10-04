#pragma once

#include <Language/AST/ParsingTools/Context.hpp>

namespace Language::Parser::Declaration
{
	inline std::unique_ptr<AST::Core::Instruction> parseDeclaration(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		context.skipSpacesAndComments();
		if (cursor.isEndOfString())
			return nullptr;
		
		const auto& parserScope = dynamic_cast<const AST::ParsingTools::ParserScope&>(scope.findScope(AST::ParsingTools::ParserScopeType));
		const auto& declarationParsers = parserScope.getDeclarationParsers();
		for (const auto& [parserName, parserFunction] : declarationParsers)
		{
			auto startPos = cursor.pos;
			try
			{
				auto declaration = parserFunction(context);
				if (declaration)
				{
					if (verbose)
						CppUtils::Log::Logger::logDebug(" -> "s + declaration->getInstructionType().name.data());
					return declaration;
				}
				cursor.pos = startPos;
			}
			catch (const std::exception& error)
			{
				cursor.pos = startPos;
				throw std::runtime_error{"In "s + parserName + ":\n" + error.what()};
			}
		}
		throw std::runtime_error{"Erreur de syntaxe. La chaine suivante ne correspond a aucune declaration connue:\n" + std::string{CppUtils::String::trimString(cursor.getNextNChar(20))} + "..."};
		return nullptr;
	}
}
