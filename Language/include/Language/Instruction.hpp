#pragma once

#include <optional>

#include "Parser.hpp"
#include "Interpreter.hpp"

namespace Language
{
	enum class eInstructionType
	{
		UNKNOWN,
		NUMBER,
		STRING,
		OBJECT,
		BRACKET,
		CONTROLSTRUCTURE,
		FUNCTIONCALL,
		FUNCTIONSTATEMENT,
		EXTERNALFUNCTION,
		OPERATOR,
		VARIABLE,
		SIGN,
		VALUE
	};

	class Instruction:
		public Parser,
		public Interpreter
	{
	public:
		Instruction() = delete;
		explicit Instruction(eInstructionType instructionType):
			m_instructionType{instructionType}
		{}
		virtual ~Instruction() = default;

		inline eInstructionType getInstructionType() const noexcept
		{
			return m_instructionType;
		}

		virtual std::unique_ptr<Instruction> cloneInstruction() const = 0;

	protected:
		eInstructionType m_instructionType;
	};
}
