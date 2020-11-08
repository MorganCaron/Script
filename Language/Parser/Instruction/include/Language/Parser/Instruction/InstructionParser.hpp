#pragma once

#include <Language/AST/ParsingTools/Context.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseInstruction(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;
		auto namespaceScopeWrapper = std::reference_wrapper<const AST::Namespace::NamespaceScope>{scope.findScope<AST::Namespace::NamespaceScope>()};
		auto hasParentScope = bool{};

		context.skipSpacesAndComments();
		if (cursor.isEndOfString())
			return nullptr;
		
		do
		{
			const auto& namespaceScope = namespaceScopeWrapper.get();
			for (const auto& namedParser : namespaceScope.instructionParsers)
			{
				const auto startPos = cursor.pos;
				try
				{
					auto instruction = namedParser.function(context);
					if (instruction)
					{
						if (verbose)
							CppUtils::Log::Logger::logDebug(" -> "s + instruction->getType().name.data());
						return instruction;
					}
					cursor.pos = startPos;
				}
				catch (const std::exception& error)
				{
					cursor.pos = startPos;
					throw std::runtime_error{"In "s + namedParser.name + ":\n" + error.what()};
				}
			}
			hasParentScope = namespaceScope.hasParentScope();
			if (hasParentScope)
				namespaceScopeWrapper = namespaceScope.getParentScope().findScope<AST::Namespace::NamespaceScope>();
		}
		while (hasParentScope);
		throw std::runtime_error{"Erreur de syntaxe. La chaine suivante ne correspond a aucune instruction connue:\n" + std::string{CppUtils::String::trimString(cursor.getNextNChar(20))} + "..."};
		return nullptr;
	}
}
