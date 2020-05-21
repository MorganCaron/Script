#pragma once

#include <any>
#include <string>
#include <unordered_map>
#include <stdexcept>

using namespace std::string_literals;

namespace Language::AST::Scope
{
	using ScopeType = unsigned int;
	constexpr static const ScopeType NormalScopeType = 0;

	class BaseScope;
	class ScopeFinder
	{
	public:
		virtual ~ScopeFinder() = default;

		virtual BaseScope& findScope(ScopeType scopeType) = 0;
		virtual const BaseScope& findScope(ScopeType scopeType) const = 0;
	};

	class Scopable;
	class BaseScope : public ScopeFinder
	{
	public:
		BaseScope() = delete;
		explicit BaseScope(ScopeType scopeType): m_type{scopeType}
		{}
		virtual ~BaseScope() = default;

		inline constexpr ScopeType getType() const noexcept
		{
			return m_type;
		}

		BaseScope& findScope(ScopeType scopeType) override;
		const BaseScope& findScope(ScopeType scopeType) const override;

	private:
		ScopeType m_type;
	};

	class Scopable: public ScopeFinder
	{
	public:
		explicit Scopable(BaseScope* scope = nullptr): m_scope{scope}
		{}
		virtual ~Scopable() = default;

		inline void setScope(BaseScope& scope) noexcept
		{
			m_scope = &scope;
		}
		BaseScope& getScope();
		const BaseScope& getScope() const;
		inline bool hasScope() const noexcept
		{
			return m_scope;
		}

		BaseScope& findScope(ScopeType scopeType) override;
		const BaseScope& findScope(ScopeType scopeType) const override;

	private:
		BaseScope* m_scope;
	};

	class NormalScope: public BaseScope, public Scopable
	{
	public:
		NormalScope(BaseScope* scope = nullptr, ScopeType scopeType = NormalScopeType): BaseScope{scopeType}, Scopable{scope}
		{}
		virtual ~NormalScope() = default;

		BaseScope& findScope(ScopeType scopeType) override final;
		const BaseScope& findScope(ScopeType scopeType) const override final;
	};
}
