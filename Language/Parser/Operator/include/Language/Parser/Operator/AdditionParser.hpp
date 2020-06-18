#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Operator/Addition.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Core::Instruction> parseAddition(AST::ParsingTools::Cursor& cursor, std::unique_ptr<AST::Core::Instruction>&& lhs)
	{
		auto& [container, scope, src, pos] = cursor;

		if (cursor.getChar() != '+' || AST::ParsingTools::OperatorChar.find(src[pos + 1]) != std::string::npos)
			return nullptr;
		
		auto addition = std::make_unique<AST::Operator::Addition>(&scope);
		auto additionParsingInformations = AST::ParsingTools::Cursor{*addition, *addition, src, ++pos};
		addition->addInstruction(std::move(lhs));
		CppUtils::Logger::logInformation(" + ", false);
		addition->addInstruction(Value::parseValue(additionParsingInformations));
		return addition;
	}
}
