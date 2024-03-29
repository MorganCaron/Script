#pragma once

#include <any>
#include <string>
#include <unordered_map>
#include <stdexcept>

using namespace std::string_literals;

namespace Script::Language::AST::Scope
{
	using ScopeType = unsigned int;

	class NormalScope
	{
	public:
		constexpr static const ScopeType Type = 0;

		explicit NormalScope(NormalScope* scope = nullptr, const ScopeType scopeType = Type):
			m_type{scopeType},
			m_parentScope{scope}
		{}
		virtual ~NormalScope() = default;

		[[nodiscard]] constexpr ScopeType getType() const noexcept
		{
			return m_type;
		}

		void setParentScope(NormalScope& parentScope) noexcept
		{
			m_parentScope = &parentScope;
		}
		[[nodiscard]] NormalScope& getParentScope()
		{
			if (!m_parentScope)
				throw std::runtime_error{"Aucun scope parent."};
			return *m_parentScope;
		}
		[[nodiscard]] const NormalScope& getParentScope() const
		{
			if (!m_parentScope)
				throw std::runtime_error{"Aucun scope parent."};
			return *m_parentScope;
		}
		[[nodiscard]] bool hasParentScope() const noexcept
		{
			return m_parentScope;
		}

		[[nodiscard]] virtual NormalScope& findScope(const ScopeType scopeType);
		[[nodiscard]] virtual const NormalScope& findScope(const ScopeType scopeType) const;

		template<class TargetScope>
		[[nodiscard]] TargetScope& findScope()
		{
			return dynamic_cast<TargetScope&>(findScope(TargetScope::Type));
		}
		template<class TargetScope>
		[[nodiscard]] const TargetScope& findScope() const
		{
			return dynamic_cast<const TargetScope&>(findScope(TargetScope::Type));
		}

	private:
		ScopeType m_type;
		NormalScope* m_parentScope;
	};
}
