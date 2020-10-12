#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Operator/NotEquality.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Operator::Operator> parseNotEquality(AST::ParsingTools::Context& context, [[maybe_unused]] const std::unique_ptr<AST::Core::Instruction>& lhs)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt("!="))
			return nullptr;
		
		auto notEquality = std::make_unique<AST::Operator::NotEquality>(&scope);
		if (verbose)
			CppUtils::Log::Logger::logInformation(" != ", false);
		return notEquality;
	}
}
