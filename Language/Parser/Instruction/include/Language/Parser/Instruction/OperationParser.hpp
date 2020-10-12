#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Instruction
{
	[[nodiscard]] inline std::unique_ptr<AST::Core::Instruction> parseOperation(AST::ParsingTools::Context& context)
	{
		auto value = Value::parseOperation(context);
		if (value != nullptr)
			context.parseSemicolon();
		return value;
	}
}
