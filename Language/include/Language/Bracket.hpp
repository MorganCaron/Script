#pragma once

#include <memory>

#include <Language/Scope/VariableScope.hpp>

#include "Instruction.hpp"
#include "InstructionContainer.hpp"

namespace Language
{
	class Bracket:
		public Instruction,
		public Scope::VariableScope,
		public InstructionContainer
	{
	public:
		explicit Bracket(BaseScope* scope = nullptr):
			Instruction{eInstructionType::BRACKET},
			VariableScope{scope}
		{}
		virtual ~Bracket() = default;

		std::unique_ptr<Instruction> cloneInstruction() const override
		{
			return std::make_unique<Bracket>(*this);
		}

		void parse(ParsingInformations& parsingInformations) override final;
		std::unique_ptr<Scope::Type::Value> interpret() override final;
	};
}
