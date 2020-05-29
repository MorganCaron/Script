#pragma once

#include <Language/AST/Scope/BaseScope.hpp>
#include <Language/AST/Scope/Type/Value.hpp>

namespace Language::AST::Scope
{
	constexpr static const ScopeType VariableScopeType = 1;

	class VariableScope: public NormalScope
	{
	public:
		struct VariableSignature
		{
			bool constant;
			std::string type;
		};
		
		VariableScope(BaseScope* scope = nullptr, ScopeType scopeType = VariableScopeType);
		VariableScope(const VariableScope& src);
		VariableScope(VariableScope&& src) noexcept = default;
		virtual ~VariableScope() = default;
		VariableScope& operator=(const VariableScope& rhs);
		VariableScope& operator=(VariableScope&& rhs) noexcept = default;

		bool variableSignatureExists(std::string_view name) const;
		bool variableExists(std::string_view name) const;
		void addVariableSignature(std::string_view name, VariableSignature&& signature);
		void setVariable(std::string_view name, std::unique_ptr<Type::Value>&& value);
		inline void resetVariableSignatures()
		{
			m_variableSignatures.clear();
		}
		inline void resetVariables()
		{
			m_variables.clear();
		}
		const VariableSignature& getVariableSignature(std::string_view name) const;
		const std::unique_ptr<Type::Value>& getVariable(std::string_view name) const;

	private:
		std::unordered_map<std::string, VariableSignature> m_variableSignatures;
		std::unordered_map<std::string, std::unique_ptr<Type::Value>> m_variables;
	};
}
