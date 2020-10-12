#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/Parser/Operator/OperatorParser.hpp>

namespace Language::Parser::Value
{
	[[nodiscard]] inline std::unique_ptr<AST::Core::Instruction> parseValue(AST::ParsingTools::Context& context)
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
			for (const auto& namedParser : namespaceScope.valueParsers)
			{
				auto startPos = cursor.pos;
				try
				{
					auto instruction = namedParser.function(context);
					if (instruction)
						return instruction;
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
		return nullptr;
	}
}
