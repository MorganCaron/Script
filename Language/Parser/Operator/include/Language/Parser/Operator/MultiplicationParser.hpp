#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Operator/Multiplication.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Core::Instruction> parseMultiplication(AST::ParsingTools::Context& context, std::unique_ptr<AST::Core::Instruction>&& lhs)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt("*"))
			return nullptr;
		
		auto multiplication = std::make_unique<AST::Operator::Multiplication>(&scope);
		auto multiplicationParsingInformations = AST::ParsingTools::Context{*multiplication, *multiplication, cursor, verbose};
		multiplication->addInstruction(std::move(lhs));
		if (verbose)
			CppUtils::Log::Logger::logInformation(" * ", false);
		auto value = Value::parseValue(multiplicationParsingInformations);
		if (value == nullptr)
			throw std::runtime_error{"L operateur * doit etre suivi d une valeur."};
		multiplication->addInstruction(std::move(value));
		return multiplication;
	}
}
