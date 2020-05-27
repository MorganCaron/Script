#include <Language/AST/Scope/VariableScope.hpp>

namespace Language::AST::Scope
{
	VariableScope::VariableScope(BaseScope* scope, ScopeType scopeType): NormalScope{scope, scopeType}
	{}

	VariableScope::VariableScope(const VariableScope& src): NormalScope{src}
	{
		for (const auto &[key, variable] : src.m_variables)
			declareVariable(key, Type::Variable{variable});
	}

	VariableScope& VariableScope::operator=(const VariableScope& rhs)
	{
		NormalScope::operator=(rhs);
		for (const auto &[key, variable] : rhs.m_variables)
			declareVariable(key, Type::Variable{variable});
		return *this;
	}

	bool VariableScope::variableExists(std::string_view name) const
	{
		if (m_variables.find(name.data()) != m_variables.end())
			return true;
		if (hasScope())
			return dynamic_cast<const VariableScope&>(getScope().findScope(getType())).variableExists(name);
		return false;
	}

	void VariableScope::declareVariable(std::string_view name, Type::Variable&& variable)
	{
		m_variables[name.data()] = std::move(variable);
	}

	void VariableScope::setVariableValue(std::string_view name, std::unique_ptr<Type::Value>&& value)
	{
		if (m_variables.find(name.data()) != m_variables.end())
		{
			auto& variable = m_variables[name.data()];
			if (variable.isConstant)
				throw std::runtime_error("La variable "s + name.data() + " est constante. Sa valeur ne peut pas etre modifiee");
			variable.value = std::move(value);
		}
		else if (hasScope())
			dynamic_cast<VariableScope&>(getScope().findScope(getType())).setVariableValue(name, std::move(value));
		else
			throw std::runtime_error("La variable "s + name.data() + " n existe pas.");
	}

	const Type::Variable& VariableScope::getVariable(std::string_view name) const
	{
		if (m_variables.find(name.data()) != m_variables.end())
			return m_variables.at(name.data());
		if (!hasScope())
			throw std::runtime_error("La variable "s + name.data() + " n existe pas.");
		return dynamic_cast<const VariableScope&>(getScope().findScope(getType())).getVariable(name);
	}
}
