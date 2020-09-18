#pragma once

#include <vector>

#include <Language/AST/Core/Instruction.hpp>

namespace Language::AST::Core
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

		[[nodiscard]] std::size_t getNbInstructions() const noexcept
		{
			return m_instructions.size();
		}

	protected:
		std::vector<std::unique_ptr<Instruction>> m_instructions;
	};
}
