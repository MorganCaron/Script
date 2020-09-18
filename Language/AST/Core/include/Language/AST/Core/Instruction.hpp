#pragma once

#include <string>
#include <optional>
#include <CppUtils.hpp>

#include <Language/AST/Core/Interpreter.hpp>

namespace Language::AST::Core
{
	class Instruction: public Interpreter
	{
	public:
		Instruction() = delete;
		explicit Instruction(CppUtils::Type::TypeId instructionType):
			m_instructionType{std::move(instructionType)}
		{}
		virtual ~Instruction() = default;

		Instruction(const Instruction&) = default;
		Instruction(Instruction&&) = default;
		Instruction& operator=(const Instruction&) = default;
		Instruction& operator=(Instruction&&) = default;

		[[nodiscard]] inline const CppUtils::Type::TypeId& getInstructionType() const noexcept
		{
			return m_instructionType;
		}

		[[nodiscard]] virtual std::unique_ptr<Instruction> cloneInstruction() const = 0;

	protected:
		CppUtils::Type::TypeId m_instructionType;
	};
}
