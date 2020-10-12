#pragma once

#include <string>
#include <memory>
#include <optional>

#include <CppUtils.hpp>
#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Core
{
	class Instruction
	{
	public:
		Instruction() = default;
		explicit Instruction(CppUtils::Type::TypeId instructionType):
			m_instructionType{std::move(instructionType)}
		{}
		Instruction(const Instruction&) = delete;
		Instruction(Instruction&&) noexcept = default;
		virtual ~Instruction() = default;
		Instruction& operator=(const Instruction&) = delete;
		Instruction& operator=(Instruction&&) noexcept = default;

		[[nodiscard]] bool isType(const CppUtils::Type::TypeId& instructionType) const noexcept
		{
			return (m_instructionType == instructionType);
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getType() const noexcept
		{
			return m_instructionType;
		}

		virtual void indexe() {};
		virtual std::unique_ptr<Type::IValue> interpret() = 0;
		[[nodiscard]] virtual const CppUtils::Type::TypeId& getReturnType() const = 0;

	protected:
		CppUtils::Type::TypeId m_instructionType;
	};

	template <typename TargetType>
	[[nodiscard]] const TargetType* ensureInstruction(const std::unique_ptr<Instruction>& instruction)
	{
		if (!instruction->isType(TargetType::Type))
			throw std::runtime_error{"Type d instruction incorrect. Instruction attendue: "s + TargetType::Type.name.data()};
		return dynamic_cast<TargetType*>(instruction.get());
	}
}
