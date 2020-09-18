#include <Language/AST/Variable/Variable.hpp>

#include <Language/AST/Type/Number.hpp>
#include <Language/AST/Variable/VariableScope.hpp>

namespace Language::AST::Variable
{
	[[nodiscard]] bool Variable::exists() const
	{
		const auto& variableScope = dynamic_cast<const VariableScope&>(getScope().findScope(VariableScopeType));
		return variableScope.variableExists(getName());
	}

	void Variable::setValue(std::unique_ptr<Type::IValue>&& value)
	{
		auto& variableScope = dynamic_cast<VariableScope&>(getScope().findScope(VariableScopeType));
		variableScope.setVariable(getName(), std::move(value));
	}

	[[nodiscard]] const std::unique_ptr<Type::IValue>& Variable::getValue() const
	{
		const auto& variableScope = dynamic_cast<const VariableScope&>(getScope().findScope(VariableScopeType));
		return variableScope.getVariable(getName());
	}
	
	std::unique_ptr<Type::IValue> Variable::interpret()
	{
		const auto &variableScope = dynamic_cast<const VariableScope&>(getScope().findScope(VariableScopeType));
		return variableScope.getVariable(getName())->cloneValue();
	}

	[[nodiscard]] const CppUtils::Type::TypeId& Variable::getReturnType() const
	{
		const auto &variableScope = dynamic_cast<const VariableScope&>(getScope().findScope(VariableScopeType));
		return variableScope.getVariableSignature(getName()).type;
	}

	std::ostream& operator<<(std::ostream& os, const Variable& variable)
	{
		os << "Variable(" << variable.getName() << ')';
		return os;
	}
}
