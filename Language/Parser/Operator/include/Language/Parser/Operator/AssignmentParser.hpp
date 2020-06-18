#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Operator/Assignment.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Core::Instruction> parseAssignment(AST::ParsingTools::Cursor& cursor, std::unique_ptr<AST::Core::Instruction>&& lhs)
	{
		auto& [container, scope, src, pos] = cursor;

		if (cursor.getChar() != '=' || AST::ParsingTools::OperatorChar.find(src[pos + 1]) != std::string::npos)
			return nullptr;
		
		auto assignment = std::make_unique<AST::Operator::Assignment>(&scope);
		auto assignmentParsingInformations = AST::ParsingTools::Cursor{*assignment, *assignment, src, ++pos};
		assignment->addInstruction(std::move(lhs));
		CppUtils::Logger::logInformation(" = ", false);
		assignment->addInstruction(Value::parseValue(assignmentParsingInformations));
		return assignment;
	}
}
