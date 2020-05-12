#pragma once

#include <Language/Scope/FileScope.hpp>

#include "InstructionContainer.hpp"

namespace Language
{
	namespace Keyword
	{
		[[maybe_unused]] static constexpr const auto SemicolonRequired = false;
		[[maybe_unused]] static constexpr const auto FunctionDeclaration = "function"sv;
		[[maybe_unused]] static constexpr const auto ImportDeclaration = "import"sv; // "import" || "include" ?
		[[maybe_unused]] static constexpr const auto ObjectDeclaration = "class"sv; // "class" || "struct" || "object" ?
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
	};
}
