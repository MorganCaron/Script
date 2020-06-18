#include <Language/AST/Scope/BaseScope.hpp>

namespace Language::AST::Scope
{
	BaseScope& BaseScope::findScope(ScopeType scopeType)
	{
		if (m_type < scopeType)
			throw std::runtime_error{"Scope introuvable."};
		return *this;
	}
	
	const BaseScope& BaseScope::findScope(ScopeType scopeType) const
	{
		if (m_type < scopeType)
			throw std::runtime_error{"Scope introuvable."};
		return *this;
	}

	BaseScope& Scopable::getScope()
	{
		if (!m_scope)
			throw std::runtime_error{"Aucun scope parent."};
		return *m_scope;
	}
	const BaseScope& Scopable::getScope() const
	{
		if (!m_scope)
			throw std::runtime_error{"Aucun scope parent."};
		return *m_scope;
	}

	BaseScope& Scopable::findScope(ScopeType scopeType)
	{
		if (!m_scope)
			throw std::runtime_error{"Scope introuvable."};
		if (m_scope->getType() >= scopeType)
			return *m_scope;
		return m_scope->findScope(scopeType);
	}

	const BaseScope& Scopable::findScope(ScopeType scopeType) const
	{
		if (!m_scope)
			throw std::runtime_error{"Scope introuvable."};
		if (m_scope->getType() >= scopeType)
			return *m_scope;
		return m_scope->findScope(scopeType);
	}

	BaseScope& NormalScope::findScope(ScopeType scopeType)
	{
		if (getType() >= scopeType)
			return *this;
		if (!hasScope())
			throw std::runtime_error{"Scope introuvable."};
		return getScope().findScope(scopeType);
	}

	const BaseScope& NormalScope::findScope(ScopeType scopeType) const
	{
		if (getType() >= scopeType)
			return *this;
		if (!hasScope())
			throw std::runtime_error{"Scope introuvable."};
		return getScope().findScope(scopeType);
	}
}
