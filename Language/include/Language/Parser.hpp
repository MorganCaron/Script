#pragma once

#include <string_view>

using namespace std::literals;

namespace Language
{
	static constexpr const auto AlphaChar = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN_"sv;
	static constexpr const auto AlphaNumChar = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN0123456789_"sv;
	static constexpr const auto SpaceChar = " \n\t"sv;
	static constexpr const auto OperatorChar = "=+*-/%<>!&|^."sv;
	static constexpr const auto NumberChar = "0123456789"sv;

	struct ParsingInformations
	{
		const std::string code;
		std::size_t pos;

		inline char currentChar() const
		{
			return code.at(pos);
		}

		inline char nextChar() const
		{
			return code.at(pos + 1);
		}

		std::string nextWord() const
		{
			auto wordLength = std::size_t{0};

			if (std::string{AlphaChar}.find(code.at(pos + wordLength)) != std::string::npos)
			{
				do
					++wordLength;
				while (std::string{AlphaNumChar}.find(code.at(pos + wordLength)) != std::string::npos);
			}
			return code.substr(pos, wordLength);
		}
	};
	
	class Parser
	{
	public:
		virtual ~Parser() = default;
		virtual void parse(ParsingInformations& parsingInformations) = 0;
	};
}
