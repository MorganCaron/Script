#pragma once

#include <Language/AST/Scope/BaseScope.hpp>
#include <Language/AST/Scope/Type/Value.hpp>

namespace Language::AST::Scope
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
		void declareVariable(std::string_view name, Type::Variable&& variable);
		void setVariableValue(std::string_view name, std::unique_ptr<Type::Value>&& value);
		inline void resetVariables()
		{
			m_variables.clear();
		}
		const Type::Variable& getVariable(std::string_view name) const;

	private:
		std::unordered_map<std::string, Type::Variable> m_variables;
	};
}
