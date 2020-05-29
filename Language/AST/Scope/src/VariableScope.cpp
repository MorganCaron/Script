#include <Language/AST/Scope/VariableScope.hpp>

namespace Language::AST::Scope
{
	VariableScope::VariableScope(BaseScope* scope, ScopeType scopeType):
		NormalScope{scope, scopeType}
	{}

	VariableScope::VariableScope(const VariableScope& src):
		NormalScope{src},
		m_variableSignatures{src.m_variableSignatures}
	{
		for (const auto &[key, value] : src.m_variables)
			setVariable(key, value->cloneValue());
	}

	VariableScope& VariableScope::operator=(const VariableScope& rhs)
	{
		NormalScope::operator=(rhs);
		m_variableSignatures = rhs.m_variableSignatures;
		for (const auto &[key, value] : rhs.m_variables)
			setVariable(key, value->cloneValue());
		return *this;
	}

	bool VariableScope::variableSignatureExists(std::string_view name) const
	{
		if (m_variableSignatures.find(name.data()) != m_variableSignatures.end())
			return true;
		if (hasScope())
		{
			const auto& parentVariableScope = dynamic_cast<const VariableScope&>(getScope().findScope(getType()));
			return parentVariableScope.variableSignatureExists(name);
		}
		return false;
	}

	bool VariableScope::variableExists(std::string_view name) const
	{
		if (m_variables.find(name.data()) != m_variables.end())
			return true;
		if (hasScope())
		{
			const auto& parentVariableScope = dynamic_cast<const VariableScope&>(getScope().findScope(getType()));
			return parentVariableScope.variableExists(name);
		}
		return false;
	}

	void VariableScope::addVariableSignature(std::string_view name, VariableSignature&& signature)
	{
		m_variableSignatures[name.data()] = std::move(signature);
	}

	void VariableScope::setVariable(std::string_view name, std::unique_ptr<Type::Value>&& value)
	{
		if (m_variableSignatures.find(name.data()) != m_variableSignatures.end())
		{
			const auto& signature = m_variableSignatures[name.data()];

			if (signature.constant && m_variables.find(name.data()) != m_variables.end())
				throw std::runtime_error{"La variable "s + name.data() + " est constante. Sa valeur ne peut pas etre modifiee"};
			
			if (value->getType() != signature.type)
				throw std::runtime_error{"La variable est de type "s + signature.type + ". Vous ne pouvez pas lui affecter une valeur de type " + value->getType().data()};

			m_variables[name.data()] = std::move(value);
		}
		else if (hasScope())
		{
			auto& parentVariableScope = dynamic_cast<VariableScope&>(getScope().findScope(getType()));
			parentVariableScope.setVariable(name, std::move(value));
		}
		else
			throw std::runtime_error{"La variable "s + name.data() + " n existe pas. Elle doit etre declaree avant d y affecter une valeur."};
	}

	const VariableScope::VariableSignature& VariableScope::getVariableSignature(std::string_view name) const
	{
		if (m_variableSignatures.find(name.data()) != m_variableSignatures.end())
			return m_variableSignatures.at(name.data());
		if (!hasScope())
			throw std::runtime_error{"La signature de la variable "s + name.data() + " n existe pas."};
		const auto& parentVariableScope = dynamic_cast<const VariableScope&>(getScope().findScope(getType()));
		return parentVariableScope.getVariableSignature(name);
	}

	const std::unique_ptr<Type::Value>& VariableScope::getVariable(std::string_view name) const
	{
		if (m_variables.find(name.data()) != m_variables.end())
			return m_variables.at(name.data());
		if (!hasScope())
			throw std::runtime_error{"La variable "s + name.data() + " n existe pas."};
		const auto& parentVariableScope = dynamic_cast<const VariableScope&>(getScope().findScope(getType()));
		return parentVariableScope.getVariable(name);
	}
}
