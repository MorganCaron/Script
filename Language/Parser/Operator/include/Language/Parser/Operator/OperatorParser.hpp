#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Core::Instruction> parseOperator(AST::ParsingTools::Cursor& cursor, std::unique_ptr<AST::Core::Instruction> lhs)
	{
		auto& [container, scope, src, pos] = cursor;

		cursor.skipSpaces();
		const auto& parserScope = dynamic_cast<const AST::ParsingTools::ParserScope&>(scope.findScope(AST::ParsingTools::ParserScopeType));
		const auto& operatorParsers = parserScope.getOperatorParsers();
		for (const auto& operatorParser : operatorParsers)
		{
			auto startPos = pos;
			auto result = operatorParser.second(cursor, std::move(lhs));
			if (pos != startPos)
				return result;
		}
		return lhs;
	}
}
