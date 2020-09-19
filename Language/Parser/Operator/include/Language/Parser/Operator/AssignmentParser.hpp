#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Operator/Assignment.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Core::Instruction> parseAssignment(AST::ParsingTools::Context& context, std::unique_ptr<AST::Core::Instruction>&& lhs)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (cursor.getChar() != '=')
			return nullptr;
		if (!cursor.isEndOfString() && cursor.src.at(cursor.pos + 1) == '=')
			return nullptr;

		auto assignment = std::make_unique<AST::Operator::Assignment>(&scope);
		++cursor.pos;
		auto assignmentParsingInformations = AST::ParsingTools::Context{*assignment, *assignment, cursor, verbose};
		assignment->addInstruction(std::move(lhs));
		if (verbose)
			CppUtils::Log::Logger::logInformation(" = ", false);
		auto value = Value::parseValue(assignmentParsingInformations);
		if (value == nullptr)
			throw std::runtime_error{"L operateur = doit etre suivi d une valeur."};
		assignment->addInstruction(std::move(value));
		return assignment;
	}
}
