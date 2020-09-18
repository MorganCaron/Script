#include <Language/AST/Scope/BaseScope.hpp>

namespace Language::AST::Scope
{
	[[nodiscard]] BaseScope& BaseScope::findScope(ScopeType scopeType)
	{
		if (m_type < scopeType)
			throw std::runtime_error{"Scope introuvable."};
		return *this;
	}
	
	[[nodiscard]] const BaseScope& BaseScope::findScope(ScopeType scopeType) const
	{
		if (m_type < scopeType)
			throw std::runtime_error{"Scope introuvable."};
		return *this;
	}

	[[nodiscard]] BaseScope& Scopable::getScope()
	{
		if (!m_scope)
			throw std::runtime_error{"Aucun scope parent."};
		return *m_scope;
	}
	[[nodiscard]] const BaseScope& Scopable::getScope() const
	{
		if (!m_scope)
			throw std::runtime_error{"Aucun scope parent."};
		return *m_scope;
	}

	[[nodiscard]] BaseScope& Scopable::findScope(ScopeType scopeType)
	{
		if (!m_scope)
			throw std::runtime_error{"Scope introuvable."};
		if (m_scope->getType() >= scopeType)
			return *m_scope;
		return m_scope->findScope(scopeType);
	}

	[[nodiscard]] const BaseScope& Scopable::findScope(ScopeType scopeType) const
	{
		if (!m_scope)
			throw std::runtime_error{"Scope introuvable."};
		if (m_scope->getType() >= scopeType)
			return *m_scope;
		return m_scope->findScope(scopeType);
	}

	[[nodiscard]] BaseScope& NormalScope::findScope(ScopeType scopeType)
	{
		if (getType() >= scopeType)
			return *this;
		if (!hasScope())
			throw std::runtime_error{"Scope introuvable."};
		return getScope().findScope(scopeType);
	}

	[[nodiscard]] const BaseScope& NormalScope::findScope(ScopeType scopeType) const
	{
		if (getType() >= scopeType)
			return *this;
		if (!hasScope())
			throw std::runtime_error{"Scope introuvable."};
		return getScope().findScope(scopeType);
	}
}
