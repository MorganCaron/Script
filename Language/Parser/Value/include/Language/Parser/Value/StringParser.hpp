#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Value/String.hpp>

namespace Language::Parser::Value
{
	inline std::string parseQuote(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos] = cursor;

		auto string = ""s;
		const auto quoteChar = cursor.getChar();

		if (quoteChar != '"' && quoteChar != '\'')
			return ""s;
		const auto length = src.length();
		while (++pos < length && cursor.getChar() != quoteChar)
			string += cursor.getChar();
		if (pos == length)
			throw std::runtime_error{(quoteChar == '"' ? "Guillemet"s : "Apostrophe"s) + " non fermes."};
		++pos;
		return string;
	}
	
	inline std::unique_ptr<AST::Core::Instruction> parseString(AST::ParsingTools::Cursor& cursor)
	{
		if (cursor.getChar() != '"' && cursor.getChar() != '\'')
			return nullptr;
		
		auto string = parseQuote(cursor);
		CppUtils::Logger::logInformation("\""s + string + '"', false);
		return std::make_unique<AST::Value::String>(std::make_unique<AST::Type::String>(std::move(string)));
	}
}
