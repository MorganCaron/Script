#pragma once

#include <Language/AST/Scope/Type/Number.hpp>
#include <Language/AST/Scope/FileScope.hpp>
#include <Language/Parser/Parser.hpp>
#include <Language/Parser/String.hpp>

namespace Language::Instruction
{
	class ImportDeclaration final:
		public AST::Instruction,
		public AST::Scope::NormalScope
	{
	public:
		static constexpr const auto Type = "Import declaration"sv;
		static constexpr const auto Keyword = "import"sv;
		
		explicit ImportDeclaration(AST::Scope::BaseScope* scope):
			AST::Instruction{std::string{Type}},
			AST::Scope::NormalScope{scope}
		{}
		
		std::unique_ptr<AST::Instruction> cloneInstruction() const override
		{
			return std::make_unique<ImportDeclaration>(*this);
		}

		static std::unique_ptr<AST::Instruction> parse(Parser::ParsingInformations& parsingInformations);
		std::unique_ptr<AST::Scope::Type::Value> interpret() override final;
	};
}
