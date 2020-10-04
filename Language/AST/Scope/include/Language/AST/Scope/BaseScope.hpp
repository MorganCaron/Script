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

		[[nodiscard]] virtual BaseScope& findScope(const ScopeType scopeType) = 0;
		[[nodiscard]] virtual const BaseScope& findScope(const ScopeType scopeType) const = 0;
	};

	class Scopable;
	class BaseScope : public ScopeFinder
	{
	public:
		BaseScope() = delete;
		explicit BaseScope(const ScopeType scopeType): m_type{scopeType}
		{}
		virtual ~BaseScope() = default;

		[[nodiscard]] inline constexpr ScopeType getType() const noexcept
		{
			return m_type;
		}

		[[nodiscard]] BaseScope& findScope(const ScopeType scopeType) override;
		[[nodiscard]] const BaseScope& findScope(const ScopeType scopeType) const override;

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
		[[nodiscard]] BaseScope& getScope();
		[[nodiscard]] const BaseScope& getScope() const;
		[[nodiscard]] inline bool hasScope() const noexcept
		{
			return m_scope;
		}

		[[nodiscard]] BaseScope& findScope(const ScopeType scopeType) override;
		[[nodiscard]] const BaseScope& findScope(const ScopeType scopeType) const override;

	private:
		BaseScope* m_scope;
	};

	class NormalScope: public BaseScope, public Scopable
	{
	public:
		NormalScope(BaseScope* scope = nullptr, const ScopeType scopeType = NormalScopeType): BaseScope{scopeType}, Scopable{scope}
		{}
		virtual ~NormalScope() = default;

		[[nodiscard]] BaseScope& findScope(const ScopeType scopeType) override;
		[[nodiscard]] const BaseScope& findScope(const ScopeType scopeType) const override;
	};
}
