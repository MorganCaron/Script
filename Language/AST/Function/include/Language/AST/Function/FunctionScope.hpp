#pragma once

#include <numeric>

#include <Language/AST/Function/Function.hpp>
#include <Language/AST/Function/FunctionSignature.hpp>
#include <Language/AST/Variable/VariableScope.hpp>

using namespace std::string_literals;

namespace Language::AST::Function
{
	constexpr static const Scope::ScopeType FunctionScopeType = 2;

	class FunctionScope: public Variable::VariableScope
	{
	public:
		explicit FunctionScope(NormalScope* scope = nullptr, Scope::ScopeType scopeType = FunctionScopeType):
			Variable::VariableScope{scope, scopeType}
		{}

		FunctionScope(const FunctionScope& src):
			Variable::VariableScope{src}
		{
			for (const auto& [key, function] : src.getFunctions())
				addFunction(key, function);
		}

		FunctionScope(FunctionScope&&) noexcept = default;
		virtual ~FunctionScope() = default;

		FunctionScope& operator=(const FunctionScope& rhs)
		{
			Variable::VariableScope::operator=(rhs);
			for (const auto& [key, function] : rhs.getFunctions())
				addFunction(key, function);
			return *this;
		}

		FunctionScope& operator=(FunctionScope&&) noexcept = default;

		inline void merge(FunctionScope& functionScope)
		{
			Variable::VariableScope::merge(functionScope);
			for (auto&& [name, function] : functionScope.m_functions)
				addFunction(name, std::move(function));
			functionScope.clearFunctions();
		}

		[[nodiscard]] bool functionExists(const FunctionSignature& functionSignature) const
		{
			if (m_functions.find(functionSignature) != m_functions.end())
				return true;
			if (hasParentScope())
				return dynamic_cast<const FunctionScope&>(getParentScope().findScope(getType())).functionExists(functionSignature);
			return false;
		}

		inline void addFunction(const FunctionSignature& functionSignature, Function function)
		{
			if (m_functions.find(functionSignature) != m_functions.end())
				throw std::runtime_error{"Function " + functionSignature.printable + " already exists."};
			m_functions[functionSignature] = std::move(function);
		}

		inline void clearFunctions() noexcept
		{
			m_functions.clear();
		}

		[[nodiscard]] inline const std::unordered_map<FunctionSignature, Function, FunctionSignature::hash_fn>& getFunctions() const noexcept
		{
			return m_functions;
		}

		[[nodiscard]] const Function& getFunction(const FunctionSignature& functionSignature) const
		{
			const auto it = m_functions.find(functionSignature);
			if (it != m_functions.end())
				return it->second;
			if (!hasParentScope())
				throw std::runtime_error{"Unknown function " + functionSignature.printable};
			return dynamic_cast<const FunctionScope&>(getParentScope().findScope(getType())).getFunction(functionSignature);
		}

	private:
		std::unordered_map<FunctionSignature, Function, FunctionSignature::hash_fn> m_functions;
	};
}
