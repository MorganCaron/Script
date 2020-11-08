#pragma once

#include <unordered_map>

#include <CppUtils.hpp>
#include <Language/AST/Operator/Operator.hpp>

namespace Language::AST::Operator
{
	class Assignment final:
		public Operator
	{
	public:
		static constexpr auto Type = CppUtils::Type::TypeId{"Assignment"};

		explicit Assignment(Scope::NormalScope* scope):
			Operator{Type, scope, eOperatorPriority::ASSIGNMENT}
		{}
		virtual ~Assignment() = default;
		
		std::unique_ptr<Type::IValue> interpret() override final
		{
			auto& operand0 = m_instructions[0];
			auto& operand1 = m_instructions[1];

			if (operand0->getType() != Variable::Variable::Type)
				throw std::runtime_error{"L operande a gauche de l operateur = doit etre une variable."};
			const auto& variableName = dynamic_cast<const Variable::Variable*>(operand0.get())->getName();

			auto value = operand1->interpret();
			auto& variableScope = dynamic_cast<Variable::VariableScope&>(getParentScope().findScope(Variable::VariableScopeType));
			variableScope.setVariable(variableName, std::move(value));
			return variableScope.getVariable(variableName)->cloneValue();
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return m_instructions[1]->getReturnType();
		}
	};
}
