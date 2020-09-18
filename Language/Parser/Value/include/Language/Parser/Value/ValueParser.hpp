#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/Parser/Operator/OperatorParser.hpp>

namespace Language::Parser::Value
{
	inline std::unique_ptr<AST::Core::Instruction> parseValue(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos, verbose] = cursor;

		cursor.skipSpaces();
		if (cursor.isEndOfCode())
			return nullptr;
		
		const auto& parserScope = dynamic_cast<const AST::ParsingTools::ParserScope&>(scope.findScope(AST::ParsingTools::ParserScopeType));
		const auto& valueParsers = parserScope.getValueParsers();
		for (const auto& [parserName, parserFunction] : valueParsers)
		{
			auto startPos = pos;
			try
			{
				auto instruction = parserFunction(cursor);
				if (instruction)
					return Operator::parseOperator(cursor, std::move(instruction));
				pos = startPos;
			}
			catch (const std::exception& error)
			{
				pos = startPos;
				throw std::runtime_error{"In "s + parserName + ":\n" + error.what()};
			}
		}
		return nullptr;
	}
}
