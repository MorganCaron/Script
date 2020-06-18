#pragma once

#include <unordered_map>

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/BaseScope.hpp>
#include <Language/AST/Type/Number.hpp>

namespace Language::AST::Operator
{
	class Addition final:
		public Core::Instruction,
		public Scope::NormalScope,
		public Core::InstructionContainer
	{
	public:
		static constexpr const auto Type = "Addition"sv;

		Addition(Scope::BaseScope* scope):
			Core::Instruction{std::string{Type}},
			Scope::NormalScope{scope}
		{}
		virtual ~Addition() = default;

		std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Addition>(*this);
		}
		
		std::unique_ptr<Type::IValue> interpret() override final
		{
			const auto& operand0 = m_instructions[0];
			const auto& operand1 = m_instructions[1];
			const auto value0 = operand0->interpret();
			const auto value1 = operand1->interpret();
			const auto number0 = Type::ensureType<Type::Number>(value0)->getValue();
			const auto number1 = Type::ensureType<Type::Number>(value1)->getValue();
			return std::make_unique<Type::Number>(number0 + number1);
		}
	};
}
