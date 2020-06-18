#pragma once

#include <string_view>

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/BaseScope.hpp>
#include <Language/AST/Instruction/Operator.hpp>

using namespace std::literals;

namespace Language::AST::ParsingTools
{
	static constexpr const auto AlphaChar = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN_"sv;
	static constexpr const auto AlphaNumChar = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN0123456789_"sv;
	static constexpr const auto SpaceChar = " \n\t"sv;
	static constexpr const auto OperatorChar = "=+*-/%<>!&|^."sv;
	static constexpr const auto NumberChar = "0123456789"sv;

	struct Cursor
	{
		explicit Cursor(Core::InstructionContainer& c_container, Scope::BaseScope& c_scope, const std::string& c_src, std::size_t& c_pos):
			container(c_container), scope(c_scope), src(c_src), pos(c_pos)
		{}

		inline bool isEndOfCode() const
		{
			return (pos >= src.length());
		}
		inline char getChar() const
		{
			return src.at(pos);
		}
		inline char getCharAndSkipIt()
		{
			return src.at(pos++);
		}
		std::string getWord() const
		{
			auto wordLength = std::size_t{0};

			if (std::string{AlphaChar}.find(src.at(pos + wordLength)) != std::string::npos)
			{
				do
					++wordLength;
				while (std::string{AlphaNumChar}.find(src.at(pos + wordLength)) != std::string::npos);
			}
			return src.substr(pos, wordLength);
		}
		std::string getWordAndSkipIt()
		{
			auto word = getWord();
			pos += word.length();
			return word;
		}
		std::string getWordRequired(std::string_view errorMessage)
		{
			auto word = getWordAndSkipIt();
			if (word.empty())
				throw std::runtime_error{errorMessage.data()};
			return word;
		}
		bool isKeywordSkipIt(std::string_view keyword)
		{
			if (getWord() != keyword)
				return false;
			pos += keyword.length();
			return true;
		}

	private:
		bool parseCommentary()
		{
			if (pos + 1 < src.size() && getChar() == '/' && src.at(pos + 1) == '/')
			{
				pos += 2;
				while (!isEndOfCode() && getChar() != '\n')
					++pos;
				if (getChar() == '\n')
					++pos;
				return true;
			}
			if (pos + 1 < src.size() && getChar() == '/' && src.at(pos + 1) == '*')
			{
				pos += 2;
				while (pos + 1 < src.size() && (getChar() != '*' || src.at(pos + 1) != '/'))
					++pos;
				if (pos + 1 == src.size())
					throw std::runtime_error{"Commentaire jamais ferme."};
				else
					pos += 2;
				return true;
			}
			return false;
		}
		
	public:
		void skipSpaces()
		{
			do
			{
				while (!isEndOfCode() && std::string{SpaceChar}.find(getChar()) != std::string::npos)
					++pos;
			} while (!isEndOfCode() && parseCommentary());
		}

		Core::InstructionContainer& container;
		Scope::BaseScope& scope;
		const std::string& src;
		std::size_t& pos;
	};

	using InstructionParser = std::function<std::unique_ptr<Core::Instruction>(Cursor&)>;
	using ValueParser = std::function<std::unique_ptr<Core::Instruction>(Cursor&)>;
	using OperatorParser = std::function<std::unique_ptr<Core::Instruction>(Cursor&, std::unique_ptr<Core::Instruction>&&)>;
}
