#pragma once

#include <vector>

#include "Instruction.hpp"

namespace Language
{
	class InstructionContainer
	{
	public:
		InstructionContainer() = default;
		InstructionContainer(const InstructionContainer& src)
		{
			for (const auto& instruction : src.m_instructions)
				addInstruction(instruction->cloneInstruction());
		}
		InstructionContainer(InstructionContainer&&) = default;
		InstructionContainer& operator=(const InstructionContainer& rhs)
		{
			for (const auto& instruction : rhs.m_instructions)
				addInstruction(instruction->cloneInstruction());
			return *this;
		}
		InstructionContainer& operator=(InstructionContainer&&) = default;

		inline void addInstruction(std::unique_ptr<Instruction>&& instruction)
		{
			m_instructions.emplace_back(std::move(instruction));
		}

	protected:
		std::vector<std::unique_ptr<Instruction>> m_instructions;
	};
}