#pragma once

#include <memory>

#include <CppUtils.hpp>

#include "Instruction.hpp"
#include "InstructionContainer.hpp"

namespace Language
{
	class Return final:
		public Instruction,
		public InstructionContainer
	{
	public:
		explicit Return(): Instruction{InstructionType::RETURN}
		{}
		virtual ~Return() = default;

		std::unique_ptr<Instruction> cloneInstruction() const override
		{
			return std::make_unique<Return>(*this);
		}
		
		void parse([[maybe_unused]] ParsingInformations& parsingInformations) override final
		{}
		std::unique_ptr<Scope::Type::Value> interpret() override final;
	};
}
