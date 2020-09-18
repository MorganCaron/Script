#pragma once

#include <functional>
#include <unordered_map>

#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/ParsingTools/ParserScope.hpp>

namespace Language
{
	class ASTRoot final:
		public AST::Core::InstructionContainer,
		public AST::ParsingTools::ParserScope
	{
	public:
		ASTRoot();
		explicit ASTRoot(std::string src);
		virtual ~ASTRoot() = default;

		void parse(const std::string src, bool verbose = false);
		void indexe();

	private:
		void addNativeRules();
	};
}
