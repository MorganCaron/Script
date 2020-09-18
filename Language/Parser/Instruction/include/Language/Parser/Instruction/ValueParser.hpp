#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseValue(AST::ParsingTools::Cursor& cursor)
	{
		auto value = Value::parseValue(cursor);
		if (value != nullptr)
			cursor.parseSemicolon();
		return value;
	}
}
