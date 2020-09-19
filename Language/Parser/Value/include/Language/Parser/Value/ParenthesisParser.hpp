#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Value
{
	inline std::unique_ptr<AST::Core::Instruction> parseParenthesis(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;
		
		if (cursor.getChar() != '(')
			return nullptr;
		++cursor.pos;
		auto instruction = parseValue(context);
		if (cursor.getChar() != ')')
			throw std::runtime_error{"Une parenthese n est pas fermee."};
		++cursor.pos;
		return instruction;
	}
}
