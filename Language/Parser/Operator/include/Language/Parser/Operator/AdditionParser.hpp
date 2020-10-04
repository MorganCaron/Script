#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Operator/Addition.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Core::Instruction> parseAddition(AST::ParsingTools::Context& context, std::unique_ptr<AST::Core::Instruction>&& lhs)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt("+"))
			return nullptr;
		
		auto addition = std::make_unique<AST::Operator::Addition>(&scope);
		auto additionParsingInformations = AST::ParsingTools::Context{*addition, *addition, cursor, verbose};
		addition->addInstruction(std::move(lhs));
		if (verbose)
			CppUtils::Log::Logger::logInformation(" + ", false);
		auto value = Value::parseValue(additionParsingInformations);
		if (value == nullptr)
			throw std::runtime_error{"L operateur + doit etre suivi d une valeur."};
		addition->addInstruction(std::move(value));
		return addition;
	}
}
