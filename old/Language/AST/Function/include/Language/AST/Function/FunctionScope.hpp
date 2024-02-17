#pragma once

#include <numeric>

#include <Language/AST/Function/Function.hpp>
#include <Language/AST/Function/FunctionSignature.hpp>
#include <Language/AST/Variable/VariableScope.hpp>

using namespace std::string_literals;

namespace Script::Language::AST::Function
{
	constexpr static const Scope::ScopeType FunctionScopeType = 2;

	class FunctionScope: public Variable::VariableScope
	{
	public:
		explicit FunctionScope(NormalScope* scope = nullptr, Scope::ScopeType scopeType = FunctionScopeType):
			Variable::VariableScope{scope, scopeType}
		{}
		FunctionScope(const FunctionScope&) = default;
		FunctionScope(FunctionScope&&) noexcept = default;
		virtual ~FunctionScope() = default;
		FunctionScope& operator=(const FunctionScope&) = default;
		FunctionScope& operator=(FunctionScope&&) noexcept = default;

		void merge(FunctionScope& functionScope)
		{
			Variable::VariableScope::merge(functionScope);
			for (auto&& [signature, function] : functionScope.m_functions)
				addFunction(signature, std::move(function));
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

		void addFunction(const FunctionSignature& functionSignature, Function function)
		{
			if (m_functions.find(functionSignature) != m_functions.end())
				throw std::runtime_error{"Function " + functionSignature.printable + " already exists."};
			m_functions[functionSignature] = std::move(function);
		}

		void clearFunctions() noexcept
		{
			m_functions.clear();
		}

		[[nodiscard]] const std::unordered_map<FunctionSignature, Function, FunctionSignature::hash_fn>& getFunctions() const noexcept
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
