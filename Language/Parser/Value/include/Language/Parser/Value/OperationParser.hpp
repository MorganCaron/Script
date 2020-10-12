#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/Parser/Value/ValueParser.hpp>
#include <Language/Parser/Operator/OperatorParser.hpp>

namespace Language::Parser::Value
{
	[[nodiscard]] inline std::unique_ptr<AST::Core::Instruction> parseOperation(AST::ParsingTools::Context& context, std::unique_ptr<AST::Core::Instruction>&& lhs = nullptr, std::unique_ptr<AST::Operator::Operator>&& nextOperator = nullptr)
	{
		auto& [container, scope, cursor, verbose] = context;
		auto rhs = std::unique_ptr<AST::Core::Instruction>{nullptr};

		if (lhs == nullptr)
			if ((lhs = Value::parseValue(context)) == nullptr)
				return nullptr;
		if (nextOperator == nullptr)
			nextOperator = Operator::parseOperator(context, lhs);
		while (nextOperator)
		{
			auto currentOperator = std::move(nextOperator);
			currentOperator->addInstruction(std::move(lhs));
			auto operatorParsingInformations = AST::ParsingTools::Context{*currentOperator, *currentOperator, cursor, verbose};
			rhs = Value::parseValue(operatorParsingInformations);
			nextOperator = Operator::parseOperator(operatorParsingInformations, lhs);
			if (nextOperator != nullptr && nextOperator->getPriority() > currentOperator->getPriority())
			{
				currentOperator->addInstruction(parseOperation(operatorParsingInformations, std::move(rhs), std::move(nextOperator)));
				return currentOperator;
			}
			else
				currentOperator->addInstruction(std::move(rhs));
			lhs = std::move(currentOperator);
		}
		return std::move(lhs);
	}
}
