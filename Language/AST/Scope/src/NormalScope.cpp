#include <Language/AST/Scope/NormalScope.hpp>

namespace Language::AST::Scope
{
	[[nodiscard]] NormalScope& NormalScope::findScope(const ScopeType scopeType)
	{
		if (getType() >= scopeType)
			return *this;
		if (!hasParentScope())
			throw std::runtime_error{"Scope introuvable."};
		return getParentScope().findScope(scopeType);
	}

	[[nodiscard]] const NormalScope& NormalScope::findScope(const ScopeType scopeType) const
	{
		if (getType() >= scopeType)
			return *this;
		if (!hasParentScope())
			throw std::runtime_error{"Scope introuvable."};
		return getParentScope().findScope(scopeType);
	}
}
