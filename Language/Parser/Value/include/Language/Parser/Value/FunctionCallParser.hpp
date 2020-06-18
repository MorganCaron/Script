#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Instruction/FunctionCall.hpp>

namespace Language::Parser::Value
{
	inline std::unique_ptr<AST::Core::Instruction> parseFunctionCall(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos] = cursor;
		
		auto functionName = cursor.getWord();
		if (functionName.empty())
			return nullptr;
		pos += functionName.length();
		cursor.skipSpaces();

		if (cursor.getChar() != '(')
			return nullptr;
		++pos;

		auto functionCall = std::make_unique<AST::Instruction::FunctionCall>(std::move(functionName), &scope);
		auto functionCallParsingInformations = AST::ParsingTools::Cursor{*functionCall, *functionCall, src, pos};
		CppUtils::Logger::logInformation(functionCall->getName().data() + "("s, false);

		cursor.skipSpaces();
		while (cursor.getChar() != ',' && cursor.getChar() != ')')
		{
			functionCall->addInstruction(parseValue(functionCallParsingInformations));
			cursor.skipSpaces();
			if (cursor.getChar() == ',')
			{
				CppUtils::Logger::logInformation(", ", false);
				++pos;
			}
		}
		if (cursor.getChar() == ')')
			++pos;
		CppUtils::Logger::logInformation(")", false);

		return functionCall;
	}
}
