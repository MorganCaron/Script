#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/Parser/Operator/OperatorParser.hpp>

namespace Language::Parser::Value
{
	inline std::unique_ptr<AST::Core::Instruction> parseValue(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos] = cursor;

		cursor.skipSpaces();
		const auto& parserScope = dynamic_cast<const AST::ParsingTools::ParserScope&>(scope.findScope(AST::ParsingTools::ParserScopeType));
		const auto& valueParsers = parserScope.getValueParsers();
		for (const auto& valueParser : valueParsers)
		{
			auto startPos = pos;
			auto instruction = valueParser.second(cursor);
			if (instruction)
				return Operator::parseOperator(cursor, std::move(instruction));
			pos = startPos;
		}
		return nullptr;
	}
}
