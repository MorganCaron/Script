#pragma once

#include <memory>

#include <CppUtils.hpp>
#include <Language/Parser/Parser.hpp>

namespace Language::Instruction
{
	class Return final:
		public AST::Instruction,
		public AST::InstructionContainer
	{
	public:
		static constexpr const auto type = "Return"sv;
		static constexpr const auto keyword = "return"sv;

		explicit Return():
			AST::Instruction{std::string{type}}
		{}

		std::unique_ptr<AST::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Return>(*this);
		}
		
		static std::unique_ptr<AST::Instruction> parse(Parser::ParsingInformations& parsingInformations);
		std::unique_ptr<AST::Scope::Type::Value> interpret() override final;
	};
}
