#include <Language/AST/Variable/VariableDeclaration.hpp>

#include <Language/AST/Type/Number.hpp>
#include <Language/AST/Variable/VariableScope.hpp>

namespace Language::AST::Variable
{
	bool VariableDeclaration::exists() const
	{
		const auto& variableScope = dynamic_cast<const Variable::VariableScope&>(getScope().findScope(Variable::VariableScopeType));
		return variableScope.variableExists(getName());
	}

	void VariableDeclaration::declare(bool constant, std::unique_ptr<Type::IValue>&& value, std::string type)
	{
		auto& variableScope = dynamic_cast<Variable::VariableScope&>(getScope().findScope(Variable::VariableScopeType));
		auto variableSignature = Variable::VariableScope::VariableSignature{constant, std::move(type)};
		variableScope.addVariableSignature(getName(), std::move(variableSignature));
		if (value != nullptr)
			variableScope.setVariable(getName(), std::move(value));
	}

	void VariableDeclaration::setValue(std::unique_ptr<Type::IValue>&& value)
	{
		auto& variableScope = dynamic_cast<Variable::VariableScope&>(getScope().findScope(Variable::VariableScopeType));
		variableScope.setVariable(getName(), std::move(value));
	}

	const std::unique_ptr<Type::IValue>& VariableDeclaration::getValue() const
	{
		const auto& variableScope = dynamic_cast<const Variable::VariableScope&>(getScope().findScope(Variable::VariableScopeType));
		return variableScope.getVariable(getName());
	}
	
	std::unique_ptr<Type::IValue> VariableDeclaration::interpret()
	{
		const auto &variableScope = dynamic_cast<const Variable::VariableScope&>(getScope().findScope(Variable::VariableScopeType));
		return variableScope.getVariable(getName())->cloneValue();
	}

	std::ostream& operator<<(std::ostream& os, const VariableDeclaration& variable)
	{
		os << "Variable declaration: " << variable.getName();
		return os;
	}
}
