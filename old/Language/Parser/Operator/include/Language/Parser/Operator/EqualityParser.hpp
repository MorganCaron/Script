#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Operator/Equality.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Script::Language::Parser::Operator
{
	std::unique_ptr<AST::Operator::Operator> parseEquality(AST::ParsingTools::Context& context, [[maybe_unused]] const std::unique_ptr<AST::Core::Instruction>& lhs)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt("=="))
			return nullptr;
		
		auto equality = std::make_unique<AST::Operator::Equality>(&scope);
		auto equalityParsingInformations = AST::ParsingTools::Context{*equality, *equality, cursor, verbose};
		if (verbose)
			CppUtils::Log::Logger::logInformation(" == ", false);
		return equality;
	}
}
