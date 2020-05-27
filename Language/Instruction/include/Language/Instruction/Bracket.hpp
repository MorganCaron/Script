#pragma once

#include <memory>

#include <Language/Parser/Parser.hpp>
#include <Language/AST/Scope/VariableScope.hpp>

namespace Language::Instruction
{
	class Bracket final:
		public AST::Instruction,
		public AST::Scope::VariableScope,
		public AST::InstructionContainer
	{
	public:
		static constexpr const auto type = "Bracket"sv;

		explicit Bracket(AST::Scope::BaseScope* scope = nullptr):
			AST::Instruction{std::string{type}},
			VariableScope{scope}
		{}
		virtual ~Bracket() = default;

		std::unique_ptr<AST::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Bracket>(*this);
		}

		static std::unique_ptr<AST::Instruction> parse(Parser::ParsingInformations& parsingInformations);
		std::unique_ptr<AST::Scope::Type::Value> interpret() override final;
	};
}
