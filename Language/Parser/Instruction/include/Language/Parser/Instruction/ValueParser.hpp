#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseValue(AST::ParsingTools::Context& context)
	{
		auto value = Value::parseValue(context);
		if (value != nullptr)
			context.parseSemicolon();
		return value;
	}
}
