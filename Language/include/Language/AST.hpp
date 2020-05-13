#pragma once

#include <Language/Scope/FileScope.hpp>
#include <Language/Scope/Type/Number.hpp>
#include <Language/Scope/Type/String.hpp>

#include "InstructionContainer.hpp"

namespace Language
{
	namespace Keyword
	{
		[[maybe_unused]] static constexpr const auto SemicolonRequired = false;
		[[maybe_unused]] static constexpr const auto ReturnStatement = "return"sv;
		[[maybe_unused]] static constexpr const auto FunctionStatement = "function"sv;
		[[maybe_unused]] static constexpr const auto ImportStatement = "import"sv; // "import" || "include" ?
		[[maybe_unused]] static constexpr const auto ObjectStatement = "class"sv; // "class" || "struct" || "object" ?
	}

	class AST:
		public InstructionContainer,
		public Scope::FileScope
	{
	public:
		AST() = default;
		explicit AST(std::string code);
		virtual ~AST() = default;

		void parse(std::string code);
		void interpret();

		static bool parseInstruction(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations);
		static bool parseCommentary(ParsingInformations& parsingInformations);
		static void parseSpace(ParsingInformations& parsingInformations);
		static void parseImport(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations);
		static void parseReturn(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations);
	};
}
