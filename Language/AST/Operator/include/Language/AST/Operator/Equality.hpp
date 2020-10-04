#pragma once

#include <unordered_map>

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/BaseScope.hpp>
#include <Language/AST/Type/Boolean.hpp>

namespace Language::AST::Operator
{
	class Equality final:
		public Core::Instruction,
		public Scope::NormalScope,
		public Core::InstructionContainer
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Equality"};

		explicit Equality(Scope::BaseScope* scope):
			Core::Instruction{Type},
			Scope::NormalScope{scope}
		{}
		virtual ~Equality() = default;

		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Equality>(*this);
		}
		
		std::unique_ptr<Type::IValue> interpret() override final
		{
			const auto& operand0 = m_instructions[0];
			const auto& operand1 = m_instructions[1];
			const auto value0 = operand0->interpret();
			const auto value1 = operand1->interpret();
			return std::make_unique<Type::Boolean>(value0->isEqual(value1));
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return Type::Boolean::TypeId;
		}
	};
}
