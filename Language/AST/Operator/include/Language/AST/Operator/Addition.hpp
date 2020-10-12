#pragma once

#include <unordered_map>

#include <CppUtils.hpp>
#include <Language/AST/Operator/Operator.hpp>
#include <Language/AST/Type/Number.hpp>

namespace Language::AST::Operator
{
	class Addition final:
		public Operator
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Addition"};

		explicit Addition(Scope::NormalScope* scope):
			Operator{Type, scope, eOperatorPriority::ARITHMETIC_LOW}
		{}
		virtual ~Addition() = default;
		
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

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return m_instructions[0]->getReturnType();
		}
	};
}
