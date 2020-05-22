#pragma once

#include <functional>
#include <unordered_map>

#include <Language/AST/InstructionContainer.hpp>
#include <Language/AST/Scope/LanguageScope.hpp>

namespace Language
{
	class ASTRoot final:
		public AST::InstructionContainer,
		public AST::Scope::LanguageScope
	{
	public:
		ASTRoot();
		explicit ASTRoot(std::string src);
		virtual ~ASTRoot() = default;

		void parse(const std::string src);
		void interpret();

	private:
		void addNativeRules();
	};
}
