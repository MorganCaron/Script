#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Value/Number.hpp>

namespace Script::Language::Parser::Value
{
	std::string getNumericString(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		auto string = ""s;
		while (!cursor.isEndOfString() && std::isdigit(cursor.getChar()))
			string += cursor.getCharAndSkipIt();
		return string;
	}
	
	std::unique_ptr<AST::Core::Instruction> parseNumber(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		auto string = getNumericString(context);
		if (!cursor.isEndOfString() && cursor.getChar() == '.')
		{
			string += cursor.getCharAndSkipIt();
			string += getNumericString(context);
		}
		
		if (string.empty() || string == ".")
			return nullptr;
		
		if (verbose)
			CppUtils::Log::Logger::logInformation(string, false);
		auto nb = std::stod(string);

		return std::make_unique<AST::Value::Number>(std::make_unique<AST::Type::Number>(nb));
	}
}
