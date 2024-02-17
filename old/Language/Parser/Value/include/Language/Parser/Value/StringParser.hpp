#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Value/String.hpp>

namespace Script::Language::Parser::Value
{
	std::string parseQuote(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		auto string = ""s;
		const auto quoteChar = cursor.getChar();

		if (quoteChar != '"' && quoteChar != '\'')
			return ""s;
		const auto length = cursor.src.length();
		while (++cursor.pos < length && cursor.getChar() != quoteChar)
			string += cursor.getChar();
		if (cursor.pos == length)
			throw std::runtime_error{(quoteChar == '"' ? "Guillemet"s : "Apostrophe"s) + " non fermes."};
		++cursor.pos;
		return string;
	}
	
	std::unique_ptr<AST::Core::Instruction> parseString(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (cursor.getChar() != '"' && cursor.getChar() != '\'')
			return nullptr;
		
		auto string = parseQuote(context);
		if (verbose)
			CppUtils::Log::Logger::logInformation("\""s + string + '"', false);
		return std::make_unique<AST::Value::String>(std::make_unique<AST::Type::String>(std::move(string)));
	}
}
