#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Operator/Member.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Script::Language::Parser::Operator
{
	[[nodiscard]] std::unique_ptr<AST::Operator::Operator> parseMember(AST::ParsingTools::Context& context, [[maybe_unused]] const std::unique_ptr<AST::Core::Instruction>& lhs)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt("."))
			return nullptr;
		
		auto member = std::make_unique<AST::Operator::Member>(&scope);
		if (verbose)
			CppUtils::Log::Logger::logInformation(".", false);
		return member;
	}
}
