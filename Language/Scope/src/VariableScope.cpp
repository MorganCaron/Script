#include "Language/Scope/VariableScope.hpp"

namespace Language::Scope
{
	VariableScope::VariableScope(BaseScope* scope, ScopeType scopeType): NormalScope(scope, scopeType)
	{}

	VariableScope::VariableScope(const VariableScope& src): NormalScope(src)
	{
		for (const auto &[key, value] : src.m_variables)
			addVariable(key, value->cloneValue());
	}

	VariableScope& VariableScope::operator=(const VariableScope& rhs)
	{
		NormalScope::operator=(rhs);
		for (const auto &[key, value] : rhs.m_variables)
			addVariable(key, value->cloneValue());
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

	void VariableScope::addVariable(std::string_view name, std::unique_ptr<Type::Value>&& value, bool local)
	{
		if (local)
		{
			m_variables[name.data()] = std::move(value);
			return;
		}
		if (m_variables.find(name.data()) != m_variables.end())
			m_variables[name.data()] = std::move(value);
		else if (hasScope())
			dynamic_cast<VariableScope&>(getScope().findScope(getType())).addVariable(name, std::move(value), local);
		else
			m_variables[name.data()] = std::move(value);
	}

	const std::unique_ptr<Type::Value>& VariableScope::getVariable(std::string_view name) const
	{
		if (m_variables.find(name.data()) != m_variables.end())
			return m_variables.at(name.data());
		if (!hasScope())
			throw std::runtime_error("La variable "s + name.data() + " n existe pas.");
		return dynamic_cast<const VariableScope&>(getScope().findScope(getType())).getVariable(name);
	}
}
