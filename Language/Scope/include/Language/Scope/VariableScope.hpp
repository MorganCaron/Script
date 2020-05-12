#pragma once

#include <Language/Scope/Type/Value.hpp>

#include "BaseScope.hpp"

namespace Language::Scope
{
	constexpr static const ScopeType VariableScopeType = 1;

	class VariableScope: public NormalScope
	{
	public:
		VariableScope(BaseScope* scope = nullptr, ScopeType scopeType = VariableScopeType);
		VariableScope(const VariableScope& src);
		VariableScope(VariableScope&& src) noexcept = default;
		virtual ~VariableScope() = default;
		VariableScope& operator=(const VariableScope& rhs);
		VariableScope& operator=(VariableScope&& rhs) noexcept = default;

		bool variableExists(std::string_view name) const;
		void addVariable(std::string_view name, std::unique_ptr<Type::Value>&& value, bool local = 0);
		inline void resetVariables()
		{
			m_variables.clear();
		}
		const std::unique_ptr<Type::Value>& getVariable(std::string_view name) const;

	private:
		std::unordered_map<std::string, std::unique_ptr<Type::Value>> m_variables;
	};
}
