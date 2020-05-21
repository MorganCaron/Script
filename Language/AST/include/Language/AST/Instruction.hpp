#pragma once

#include <optional>

#include <Language/AST/Interpreter.hpp>

namespace Language::AST
{
	enum class InstructionType
	{
		UNKNOWN,
		NUMBER,
		STRING,
		OBJECT,
		BRACKET,
		CONTROLSTRUCTURE,
		FUNCTIONCALL,
		FUNCTIONSTATEMENT,
		IMPORTSTATEMENT,
		EXTERNALFUNCTION,
		OPERATOR,
		VARIABLE,
		SIGN,
		VALUE,
		RETURN
	};

	class Instruction: public Interpreter
	{
	public:
		Instruction() = delete;
		explicit Instruction(InstructionType instructionType):
			m_instructionType{instructionType}
		{}
		virtual ~Instruction() = default;

		inline InstructionType getInstructionType() const noexcept
		{
			return m_instructionType;
		}

		virtual std::unique_ptr<Instruction> cloneInstruction() const = 0;

	protected:
		InstructionType m_instructionType;
	};
}
