#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Operator/Multiplication.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Operator::Operator> parseMultiplication(AST::ParsingTools::Context& context, [[maybe_unused]] const std::unique_ptr<AST::Core::Instruction>& lhs)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt("*"))
			return nullptr;
		
		auto multiplication = std::make_unique<AST::Operator::Multiplication>(&scope);
		if (verbose)
			CppUtils::Log::Logger::logInformation(" * ", false);
		return multiplication;
	}
}
