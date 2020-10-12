#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Operator/Assignment.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Operator::Operator> parseAssignment(AST::ParsingTools::Context& context, [[maybe_unused]] const std::unique_ptr<AST::Core::Instruction>& lhs)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (cursor.getChar() != '=')
			return nullptr;
		if (!cursor.isEndOfString() && cursor.src.at(cursor.pos + 1) == '=')
			return nullptr;
		++cursor.pos;

		auto assignment = std::make_unique<AST::Operator::Assignment>(&scope);
		if (verbose)
			CppUtils::Log::Logger::logInformation(" = ", false);
		return assignment;
	}
}
