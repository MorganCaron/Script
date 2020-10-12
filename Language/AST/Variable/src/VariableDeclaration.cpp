#include <Language/AST/Variable/VariableDeclaration.hpp>

#include <Language/AST/Type/Number.hpp>
#include <Language/AST/Variable/VariableScope.hpp>

namespace Language::AST::Variable
{
	[[nodiscard]] bool VariableDeclaration::exists() const
	{
		const auto& variableScope = dynamic_cast<const Variable::VariableScope&>(getParentScope().findScope(Variable::VariableScopeType));
		return variableScope.variableExists(getName());
	}

	void VariableDeclaration::declare(VariableSignature variableSignature)
	{
		auto& variableScope = dynamic_cast<Variable::VariableScope&>(getParentScope().findScope(Variable::VariableScopeType));
		variableScope.addVariableSignature(std::move(variableSignature));
	}

	void VariableDeclaration::setValue(std::unique_ptr<Type::IValue>&& value)
	{
		auto& variableScope = dynamic_cast<Variable::VariableScope&>(getParentScope().findScope(Variable::VariableScopeType));
		variableScope.setVariable(getName(), std::move(value));
	}

	[[nodiscard]] const std::unique_ptr<Type::IValue>& VariableDeclaration::getValue() const
	{
		const auto& variableScope = dynamic_cast<const Variable::VariableScope&>(getParentScope().findScope(Variable::VariableScopeType));
		return variableScope.getVariable(getName());
	}

	void VariableDeclaration::indexe()
	{
		CppUtils::Log::Logger::logDetail("Declare variable "s + getName().data());
		interpret();
	}
	
	std::unique_ptr<Type::IValue> VariableDeclaration::interpret()
	{
		auto &variableScope = dynamic_cast<Variable::VariableScope&>(getParentScope().findScope(Variable::VariableScopeType));

		if (m_instructions.empty())
			return std::make_unique<Type::Number>(0);
		
		auto& valueInstruction = *m_instructions[0];
		auto value = valueInstruction.interpret();
		variableScope.setVariable(getName(), value->cloneValue());
		return value;
	}

	[[nodiscard]] const CppUtils::Type::TypeId& VariableDeclaration::getReturnType() const
	{
		const auto &variableScope = dynamic_cast<const Variable::VariableScope&>(getParentScope().findScope(Variable::VariableScopeType));
		return variableScope.getVariableSignature(getName()).type;
	}

	std::ostream& operator<<(std::ostream& os, const VariableDeclaration& variable)
	{
		os << "Variable declaration: " << variable.getName();
		return os;
	}
}
