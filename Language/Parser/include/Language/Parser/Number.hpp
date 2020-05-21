#pragma once

#include <Language/Parser/Parser.hpp>
#include <Language/AST/Scope/Type/Number.hpp>

namespace Language::Parser
{
	inline std::unique_ptr<AST::Scope::Type::Number> parseNumber(ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;
		auto buffer = std::string{};
		auto nb = double{};

		while (std::string{NumberChar}.find(parsingInformations.currentChar()) != std::string::npos)
			buffer += src.at(pos++);
		if (parsingInformations.currentChar() == '.')
			buffer += src.at(pos++);
		while (std::string{NumberChar}.find(parsingInformations.currentChar()) != std::string::npos)
			buffer += src.at(pos++);
		if (!buffer.empty())
		{
			CppUtils::Logger::logInformation(buffer, false);
			std::stringstream ss(buffer.c_str());
			ss >> nb;
			return std::make_unique<AST::Scope::Type::Number>(nb);
		}
		return nullptr;
	}
}
