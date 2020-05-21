#pragma once

#include <Language/Parser/Parser.hpp>
#include <Language/AST/Scope/Type/String.hpp>

namespace Language::Parser
{
	inline std::unique_ptr<AST::Scope::Type::String> parseString(ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;
		auto quoteChar = parsingInformations.currentChar();

		if (quoteChar != '"' && quoteChar != '\'')
			return nullptr;
		
		auto buffer = std::string{};
		auto length = src.length();
		while (++pos < length && parsingInformations.currentChar() != quoteChar)
			buffer += parsingInformations.currentChar();
		if (pos == length)
			throw std::runtime_error{std::string(quoteChar == '"' ? "Guillemet" : "Apostrophe") + " non fermes."};
		++pos;
		CppUtils::Logger::logInformation("\""s + buffer + '"', false);
		return std::make_unique<AST::Scope::Type::String>(buffer);
	}
}
