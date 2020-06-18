#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Value/Number.hpp>

namespace Language::Parser::Value
{
	inline bool isNumber(AST::ParsingTools::Cursor& cursor)
	{
		return (cursor.getChar() == '.' || std::string{AST::ParsingTools::NumberChar}.find(cursor.getChar()) != std::string::npos);
	}

	inline std::string getNumericString(AST::ParsingTools::Cursor& cursor)
	{
		auto string = ""s;
		while (std::string{AST::ParsingTools::NumberChar}.find(cursor.getChar()) != std::string::npos)
			string += cursor.getCharAndSkipIt();
		return string;
	}
	
	inline double parseDouble(AST::ParsingTools::Cursor& cursor)
	{
		auto string = getNumericString(cursor);
		if (cursor.getChar() == '.')
			string += cursor.getCharAndSkipIt();
		string += getNumericString(cursor);
		
		CppUtils::Logger::logInformation(string, false);

		return std::stod(string);
	}
	
	inline std::unique_ptr<AST::Core::Instruction> parseNumber(AST::ParsingTools::Cursor& cursor)
	{
		return isNumber(cursor) ? std::make_unique<AST::Value::Number>(std::make_unique<AST::Type::Number>(parseDouble(cursor))) : nullptr;
	}
}
