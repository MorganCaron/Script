#pragma once

#include <string>
#include <optional>

#include <Language/AST/Interpreter.hpp>

namespace Language::AST
{
	class Instruction: public Interpreter
	{
	public:
		Instruction() = delete;
		explicit Instruction(std::string instructionType):
			m_instructionType{std::move(instructionType)}
		{}
		virtual ~Instruction() = default;

		Instruction(const Instruction&) = default;
		Instruction(Instruction&&) = default;
		Instruction& operator=(const Instruction&) = default;
		Instruction& operator=(Instruction&&) = default;

		inline const std::string& getInstructionType() const noexcept
		{
			return m_instructionType;
		}

		virtual std::unique_ptr<Instruction> cloneInstruction() const = 0;

	protected:
		std::string m_instructionType;
	};
}
