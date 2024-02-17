#pragma once

#include <Language/AST/ParsingTools/Context.hpp>

namespace Script::Language::Parser::Operator
{
	[[nodiscard]] std::unique_ptr<AST::Operator::Operator> parseOperator(AST::ParsingTools::Context& context, const std::unique_ptr<AST::Core::Instruction>& lhs)
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
			for (const auto& namedParser : namespaceScope.operatorParsers)
			{
				const auto startPos = cursor.pos;
				try
				{
					auto result = namedParser.function(context, lhs);
					if (cursor.pos != startPos)
						return result;
				}
				catch (const std::exception& error)
				{
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
