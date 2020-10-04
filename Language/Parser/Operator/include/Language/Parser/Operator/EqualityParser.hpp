#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Operator/Equality.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Core::Instruction> parseEquality(AST::ParsingTools::Context& context, std::unique_ptr<AST::Core::Instruction>&& lhs)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt("=="))
			return nullptr;
		
		auto equality = std::make_unique<AST::Operator::Equality>(&scope);
		auto equalityParsingInformations = AST::ParsingTools::Context{*equality, *equality, cursor, verbose};
		equality->addInstruction(std::move(lhs));
		if (verbose)
			CppUtils::Log::Logger::logInformation(" == ", false);
		auto value = Value::parseValue(equalityParsingInformations);
		if (value == nullptr)
			throw std::runtime_error{"L operateur == doit etre suivi d une valeur."};
		equality->addInstruction(std::move(value));
		return equality;
	}
}
