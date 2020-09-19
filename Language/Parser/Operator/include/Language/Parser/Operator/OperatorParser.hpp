#pragma once

#include <Language/AST/ParsingTools/Context.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Core::Instruction> parseOperator(AST::ParsingTools::Context& context, std::unique_ptr<AST::Core::Instruction> lhs)
	{
		auto& [container, scope, cursor, verbose] = context;

		context.skipSpacesAndComments();
		if (cursor.isEndOfString())
			return lhs;
		
		const auto& parserScope = dynamic_cast<const AST::ParsingTools::ParserScope&>(scope.findScope(AST::ParsingTools::ParserScopeType));
		const auto& operatorParsers = parserScope.getOperatorParsers();
		for (const auto& [parserName, parserFunction] : operatorParsers)
		{
			auto startPos = cursor.pos;
			try
			{
				auto result = parserFunction(context, std::move(lhs));
				if (cursor.pos != startPos)
					return result;
			}
			catch (const std::exception& error)
			{
				throw std::runtime_error{"In "s + parserName + ":\n" + error.what()};
			}
		}
		return lhs;
	}
}
