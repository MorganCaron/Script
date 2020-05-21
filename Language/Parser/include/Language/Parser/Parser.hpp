#pragma once

#include <string_view>

#include <CppUtils.hpp>
#include <Language/AST/InstructionContainer.hpp>
#include <Language/AST/Scope/BaseScope.hpp>

using namespace std::literals;

namespace Language::Parser
{
	static constexpr const auto AlphaChar = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN_"sv;
	static constexpr const auto AlphaNumChar = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN0123456789_"sv;
	static constexpr const auto SpaceChar = " \n\t"sv;
	static constexpr const auto OperatorChar = "=+*-/%<>!&|^."sv;
	static constexpr const auto NumberChar = "0123456789"sv;

	struct ParsingInformations
	{
		explicit ParsingInformations(AST::InstructionContainer& c_container, AST::Scope::BaseScope& c_scope, const std::string& c_src, std::size_t& c_pos):
			container(c_container), scope(c_scope), src(c_src), pos(c_pos)
		{}

		inline bool endOfCode() const
		{
			return (pos >= src.size());
		}
		inline char currentChar() const
		{
			return src.at(pos);
		}
		inline char nextChar() const
		{
			return src.at(pos + 1);
		}
		std::string nextWord() const;
	private:
		bool parseCommentary();
	public:
		void skipSpaces();
		std::unique_ptr<AST::Instruction> parseInstruction();

		AST::InstructionContainer& container;
		AST::Scope::BaseScope& scope;
		const std::string& src;
		std::size_t& pos;
	};

	using InstructionParser = std::function<std::unique_ptr<AST::Instruction>(ParsingInformations& parsingInformations)>;
}
