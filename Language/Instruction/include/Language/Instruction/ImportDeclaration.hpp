#pragma once

#include <Language/AST/Scope/Type/Number.hpp>
#include <Language/AST/Scope/FileScope.hpp>
#include <Language/Parser/Parser.hpp>
#include <Language/Parser/String.hpp>

namespace Language::Instruction
{
	class ImportDeclaration final: public AST::Instruction
	{
	public:
		static constexpr const auto type = "Import declaration"sv;
		static constexpr const auto keyword = "import"sv;
		
		explicit ImportDeclaration():
			AST::Instruction{std::string{type}}
		{}
		
		std::unique_ptr<AST::Instruction> cloneInstruction() const override
		{
			return std::make_unique<ImportDeclaration>(*this);
		}

		static std::unique_ptr<AST::Instruction> parse(Parser::ParsingInformations& parsingInformations);
		std::unique_ptr<AST::Scope::Type::Value> interpret() override final;
	};
}
