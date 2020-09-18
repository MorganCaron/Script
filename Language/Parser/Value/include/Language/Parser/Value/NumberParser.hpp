#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Value/Number.hpp>

namespace Language::Parser::Value
{
	inline std::string getNumericString(AST::ParsingTools::Cursor& cursor)
	{
		auto string = ""s;
		while (!cursor.isEndOfCode() && std::isdigit(cursor.getChar()))
			string += cursor.getCharAndSkipIt();
		return string;
	}
	
	inline std::unique_ptr<AST::Core::Instruction> parseNumber(AST::ParsingTools::Cursor& cursor)
	{
		auto string = getNumericString(cursor);
		if (!cursor.isEndOfCode() && cursor.getChar() == '.')
		{
			string += cursor.getCharAndSkipIt();
			string += getNumericString(cursor);
		}
		
		if (string.empty() || string == ".")
			return nullptr;
		
		if (cursor.verbose)
			CppUtils::Log::Logger::logInformation(string, false);
		auto nb = std::stod(string);

		return std::make_unique<AST::Value::Number>(std::make_unique<AST::Type::Number>(nb));
	}
}
