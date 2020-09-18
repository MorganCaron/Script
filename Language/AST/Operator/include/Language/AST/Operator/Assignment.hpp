#pragma once

#include <unordered_map>

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/BaseScope.hpp>

namespace Language::AST::Operator
{
	class Assignment final:
		public Core::Instruction,
		public Scope::NormalScope,
		public Core::InstructionContainer
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Assignment"};

		Assignment(Scope::BaseScope* scope):
			Core::Instruction{Type},
			Scope::NormalScope{scope}
		{}
		virtual ~Assignment() = default;

		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Assignment>(*this);
		}
		
		std::unique_ptr<Type::IValue> interpret() override final
		{
			auto& operand0 = m_instructions[0];
			auto& operand1 = m_instructions[1];

			if (operand0->getInstructionType() != Variable::Variable::Type)
				throw std::runtime_error{"L operande a gauche de l operateur = doit etre une variable."};
			const auto& variableName = dynamic_cast<const Variable::Variable*>(operand0.get())->getName();

			auto value = operand1->interpret();
			auto& variableScope = dynamic_cast<Variable::VariableScope&>(getScope().findScope(Variable::VariableScopeType));
			variableScope.setVariable(variableName, std::move(value));
			return variableScope.getVariable(variableName)->cloneValue();
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return m_instructions[1]->getReturnType();
		}
	};
}
