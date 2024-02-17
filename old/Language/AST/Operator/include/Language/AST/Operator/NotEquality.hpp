#pragma once

#include <unordered_map>

#include <CppUtils.hpp>
#include <Language/AST/Operator/Operator.hpp>
#include <Language/AST/Type/Boolean.hpp>

namespace Script::Language::AST::Operator
{
	class NotEquality final:
		public Operator
	{
	public:
		static constexpr auto Type = CppUtils::Type::Token{"Not Equality"};

		explicit NotEquality(Scope::NormalScope* scope):
			Operator{Type, scope, eOperatorPriority::COMPARISON}
		{}
		virtual ~NotEquality() = default;
		
		std::unique_ptr<Type::IValue> interpret() override final
		{
			const auto& operand0 = m_instructions[0];
			const auto& operand1 = m_instructions[1];
			const auto value0 = operand0->interpret();
			const auto value1 = operand1->interpret();
			return std::make_unique<Type::Boolean>(!value0->isEqual(value1));
		}

		[[nodiscard]] const CppUtils::Type::Token& getReturnType() const override final
		{
			return Type::Boolean::Token;
		}
	};
}
