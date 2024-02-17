#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Operator/Addition.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Script::Language::Parser::Operator
{
	std::unique_ptr<AST::Operator::Operator> parseAddition(AST::ParsingTools::Context& context, [[maybe_unused]] const std::unique_ptr<AST::Core::Instruction>& lhs)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt("+"))
			return nullptr;
		
		auto addition = std::make_unique<AST::Operator::Addition>(&scope);
		if (verbose)
			CppUtils::Log::Logger::logInformation(" + ", false);
		return addition;
	}
}
