#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Core::Instruction> parseOperator(AST::ParsingTools::Cursor& cursor, std::unique_ptr<AST::Core::Instruction> lhs)
	{
		auto& [container, scope, src, pos, verbose] = cursor;

		cursor.skipSpaces();
		if (cursor.isEndOfCode())
			return lhs;
		
		const auto& parserScope = dynamic_cast<const AST::ParsingTools::ParserScope&>(scope.findScope(AST::ParsingTools::ParserScopeType));
		const auto& operatorParsers = parserScope.getOperatorParsers();
		for (const auto& [parserName, parserFunction] : operatorParsers)
		{
			auto startPos = pos;
			try
			{
				auto result = parserFunction(cursor, std::move(lhs));
				if (pos != startPos)
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
