#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Value
{
	inline std::unique_ptr<AST::Core::Instruction> parseParenthesis(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos, verbose] = cursor;
		
		if (cursor.getChar() != '(')
			return nullptr;
		++pos;
		auto instruction = parseValue(cursor);
		if (cursor.getChar() != ')')
			throw std::runtime_error{"Une parenthese n est pas fermee."};
		++pos;
		return instruction;
	}
}
