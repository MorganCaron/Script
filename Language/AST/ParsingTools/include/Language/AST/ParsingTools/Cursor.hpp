#pragma once

#include <string_view>

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/BaseScope.hpp>
#include <Language/AST/Instruction/Operator.hpp>

using namespace std::literals;

namespace Language::AST::ParsingTools
{
	struct Cursor
	{
		explicit Cursor(Core::InstructionContainer& c_container, Scope::BaseScope& c_scope, const std::string& c_src, std::size_t& c_pos, bool c_verbose):
			container{c_container}, scope{c_scope}, src{c_src}, pos{c_pos}, verbose{c_verbose}
		{}

		[[nodiscard]] inline bool isEndOfCode() const noexcept
		{
			return (pos >= src.length());
		}
		
		[[nodiscard]] inline char getChar() const
		{
			return src.at(pos);
		}

		[[nodiscard]] inline char getCharAndSkipIt()
		{
			return src.at(pos++);
		}

		[[nodiscard]] inline std::string getNextNChar(const std::size_t size) const
		{
			return src.substr(pos, std::min(size, src.length() - pos));
		}

		[[nodiscard]] std::string getWord() const
		{
			auto wordLength = std::size_t{0};

			if (std::isalpha(src.at(pos + wordLength)) || src.at(pos + wordLength) == '_')
			{
				do
					++wordLength;
				while (std::isalnum(src.at(pos + wordLength)) || src.at(pos + wordLength) == '_');
			}
			return src.substr(pos, wordLength);
		}

		[[nodiscard]] std::string getWordAndSkipIt()
		{
			auto word = getWord();
			pos += word.length();
			return word;
		}

		[[nodiscard]] std::string getWordRequired(std::string_view errorMessage)
		{
			auto word = getWordAndSkipIt();
			if (word.empty())
				throw std::runtime_error{errorMessage.data()};
			return word;
		}

		bool isKeywordSkipIt(std::string_view keyword)
		{
			const auto length = keyword.length();
			if (getNextNChar(length) != keyword)
				return false;
			pos += length;
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
				while (!isEndOfCode() && std::isspace(getChar()))
					++pos;
			} while (!isEndOfCode() && parseCommentary());
		}

		void parseSemicolon()
		{
			skipSpaces();
			if (isEndOfCode() || getChar() != ';')
				CppUtils::Log::Logger::logWarning("You forgot a semicolon after an instruction.\nSemicolons avoid misunderstandings by separating each instruction separately.\nWithout a semicolon, Script may think that two instructions form an operation if an operator is found between them.");
			else if (verbose)
				CppUtils::Log::Logger::logInformation(";", false);
			++pos;
		}

		Core::InstructionContainer& container;
		Scope::BaseScope& scope;
		const std::string& src;
		std::size_t& pos;
		bool verbose;
	};

	using DeclarationParser = std::function<std::unique_ptr<Core::Instruction>(Cursor&)>;
	using InstructionParser = std::function<std::unique_ptr<Core::Instruction>(Cursor&)>;
	using ValueParser = std::function<std::unique_ptr<Core::Instruction>(Cursor&)>;
	using OperatorParser = std::function<std::unique_ptr<Core::Instruction>(Cursor&, std::unique_ptr<Core::Instruction>&&)>;
}
