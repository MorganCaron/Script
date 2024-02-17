#pragma once

#include <vector>

#include <Language/AST/Core/Instruction.hpp>

namespace Script::Language::AST::Core
{
	class InstructionContainer:
		public Instruction
	{
	public:
		InstructionContainer() = default;
		explicit InstructionContainer(CppUtils::Type::Token instructionType):
			Instruction{std::move(instructionType)}
		{}

		void addInstruction(std::unique_ptr<Instruction>&& instruction)
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
