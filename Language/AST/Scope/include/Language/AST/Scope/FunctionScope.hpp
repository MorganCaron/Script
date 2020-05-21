#pragma once

#include <Language/AST/Scope/Type/Value.hpp>
#include <Language/AST/Scope/Type/Function.hpp>
#include <Language/AST/Scope/VariableScope.hpp>

namespace Language::AST::Scope
{
	using FunctionType = Type::ITFunction<std::unique_ptr<Type::Value>(const Type::Args&)>;

	constexpr static const ScopeType FunctionScopeType = 2;

	class FunctionScope: public VariableScope
	{
	public:
		FunctionScope(BaseScope* scope = nullptr, ScopeType scopeType = FunctionScopeType):
			VariableScope{scope, scopeType}
		{}
		FunctionScope(const FunctionScope& src): VariableScope{src}
		{
			for (const auto& [key, value] : src.getFunctions())
				addFunction(key, value->cloneFunction());
		}
		FunctionScope(FunctionScope&&) noexcept = default;
		virtual ~FunctionScope() = default;
		FunctionScope& operator=(const FunctionScope& rhs)
		{
			VariableScope::operator=(rhs);
			for (const auto& [key, value] : rhs.m_functions)
				addFunction(key, value->cloneFunction());
			return *this;
		}
		FunctionScope& operator=(FunctionScope&&) noexcept = default;

		bool functionExists(std::string_view name) const
		{
			if (m_functions.find(name.data()) != m_functions.end())
				return true;
			if (hasScope())
				return dynamic_cast<const FunctionScope&>(getScope().findScope(getType())).functionExists(name);
			return false;
		}

		inline void addFunction(std::string_view name, std::unique_ptr<FunctionType>&& function)
		{
			m_functions[name.data()] = std::move(function);
		}

		inline void resetFunctions() noexcept
		{
			m_functions.clear();
		}

		inline const std::unordered_map<std::string, std::unique_ptr<FunctionType>>& getFunctions() const
		{
			return m_functions;
		}

		[[maybe_unused]] FunctionType& getFunction(std::string_view name) const
		{
			if (m_functions.find(name.data()) != m_functions.end())
				return *m_functions.at(name.data());
			if (!hasScope())
				throw std::runtime_error{"Unknown function "s + name.data() + "."};
			return dynamic_cast<const FunctionScope&>(getScope().findScope(getType())).getFunction(name);
		}

	private:
		std::unordered_map<std::string, std::unique_ptr<FunctionType>> m_functions;
	};
}
