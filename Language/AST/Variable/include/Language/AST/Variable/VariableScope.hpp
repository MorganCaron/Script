#pragma once

#include <string>

#include <Language/AST/Scope/BaseScope.hpp>
#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Variable
{
	struct VariableSignature
	{
		std::string name;
		bool constant;
		CppUtils::Type::TypeId type;

		VariableSignature() = default;
		
		VariableSignature(std::string c_name, bool c_constant, CppUtils::Type::TypeId c_type):
			name{std::move(c_name)},
			constant{c_constant},
			type{std::move(c_type)}
		{}

		[[nodiscard]] bool operator==(const VariableSignature& rhs) const
		{
			return name == rhs.name;
		}
	};
	
	constexpr static const Scope::ScopeType VariableScopeType = 1;

	class VariableScope: public Scope::NormalScope
	{
	public:
		VariableScope(BaseScope* scope = nullptr, Scope::ScopeType scopeType = VariableScopeType):
			NormalScope{scope, scopeType}
		{}
		
		VariableScope(const VariableScope& src):
			NormalScope{src},
			m_variableSignatures{src.m_variableSignatures}
		{
			for (const auto &[key, value] : src.m_variables)
				setVariable(key, value->cloneValue());
		}

		VariableScope(VariableScope&&) noexcept = default;
		virtual ~VariableScope() = default;

		VariableScope& operator=(const VariableScope& rhs)
		{
			NormalScope::operator=(rhs);
			m_variableSignatures = rhs.m_variableSignatures;
			for (const auto &[key, value] : rhs.m_variables)
				setVariable(key, value->cloneValue());
			return *this;
		}

		VariableScope& operator=(VariableScope&&) noexcept = default;

		inline void merge(VariableScope& variableScope)
		{
			for (auto&& [name, variableSignature] : variableScope.m_variableSignatures)
				addVariableSignature(std::move(variableSignature));
			for (auto&& [name, value] : variableScope.m_variables)
				setVariable(name, std::move(value));
			variableScope.clearVariableSignatures();
		}

		[[nodiscard]] bool variableSignatureExists(std::string_view name) const
		{
			if (m_variableSignatures.find(name.data()) != m_variableSignatures.end())
				return true;
			if (hasScope())
			{
				const auto& parentVariableScope = dynamic_cast<const VariableScope&>(getScope().findScope(getType()));
				return parentVariableScope.variableSignatureExists(name);
			}
			return false;
		}

		[[nodiscard]] bool variableExists(std::string_view name) const
		{
			if (m_variables.find(name.data()) != m_variables.end())
				return true;
			if (hasScope())
			{
				const auto& parentVariableScope = dynamic_cast<const VariableScope&>(getScope().findScope(getType()));
				return parentVariableScope.variableExists(name);
			}
			return false;
		}

		void addVariableSignature(VariableSignature variableSignature)
		{
			m_variableSignatures[variableSignature.name] = std::move(variableSignature);
		}

		void setVariable(std::string_view name, std::unique_ptr<Type::IValue>&& value)
		{
			if (m_variableSignatures.find(name.data()) != m_variableSignatures.end())
			{
				const auto& signature = m_variableSignatures.at(name.data());

				if (signature.constant && m_variables.find(name.data()) != m_variables.end())
					throw std::runtime_error{"The variable "s + name.data() + " is constant. Its value cannot be modified."};
				/*
				if (value->getInstructionType() != signature.type)
					throw std::runtime_error{"La variable est de type "s + signature.type + ". Vous ne pouvez pas lui affecter une valeur de type " + value->getType().data()};
				*/
				m_variables[name.data()] = std::move(value);
			}
			else if (hasScope())
			{
				auto& parentVariableScope = dynamic_cast<VariableScope&>(getScope().findScope(getType()));
				parentVariableScope.setVariable(name, std::move(value));
			}
			else
				throw std::runtime_error{"The variable "s + name.data() + " does not exist. It must be declared before assigning it a value."};
		}

		inline void clearVariableSignatures()
		{
			m_variableSignatures.clear();
			clearVariables();
		}

		inline void clearVariables()
		{
			m_variables.clear();
		}

		[[nodiscard]] const VariableSignature& getVariableSignature(std::string_view name) const
		{
			if (m_variableSignatures.find(name.data()) != m_variableSignatures.end())
				return m_variableSignatures.at(name.data());
			if (!hasScope())
				throw std::runtime_error{"The signature of variable "s + name.data() + " does not exist."};
			const auto& parentVariableScope = dynamic_cast<const VariableScope&>(getScope().findScope(getType()));
			return parentVariableScope.getVariableSignature(name);
		}

		[[nodiscard]] const std::unique_ptr<Type::IValue>& getVariable(std::string_view name) const
		{
			if (m_variables.find(name.data()) != m_variables.end())
				return m_variables.at(name.data());
			if (!hasScope())
				throw std::runtime_error{"The variable "s + name.data() + " does not exist."};
			const auto& parentVariableScope = dynamic_cast<const VariableScope&>(getScope().findScope(getType()));
			return parentVariableScope.getVariable(name);
		}

	private:
		std::unordered_map<std::string, VariableSignature> m_variableSignatures;
		std::unordered_map<std::string, std::unique_ptr<Type::IValue>> m_variables;
	};
}
