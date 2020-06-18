#include <Language/AST/Variable/Variable.hpp>

#include <Language/AST/Type/Number.hpp>
#include <Language/AST/Variable/VariableScope.hpp>

namespace Language::AST::Variable
{
	bool Variable::exists() const
	{
		const auto& variableScope = dynamic_cast<const VariableScope&>(getScope().findScope(VariableScopeType));
		return variableScope.variableExists(getName());
	}

	void Variable::setValue(std::unique_ptr<Type::IValue>&& value)
	{
		auto& variableScope = dynamic_cast<VariableScope&>(getScope().findScope(VariableScopeType));
		variableScope.setVariable(getName(), std::move(value));
	}

	const std::unique_ptr<Type::IValue>& Variable::getValue() const
	{
		const auto& variableScope = dynamic_cast<const VariableScope&>(getScope().findScope(VariableScopeType));
		return variableScope.getVariable(getName());
	}
	
	std::unique_ptr<Type::IValue> Variable::interpret()
	{
		const auto &variableScope = dynamic_cast<const VariableScope&>(getScope().findScope(VariableScopeType));
		return variableScope.getVariable(getName())->cloneValue();
	}

	std::ostream& operator<<(std::ostream& os, const Variable& variable)
	{
		os << "Variable(" << variable.getName() << ')';
		return os;
	}
}
