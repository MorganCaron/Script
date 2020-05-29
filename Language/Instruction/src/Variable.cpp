#include <Language/Instruction/Variable.hpp>

#include <Language/AST/Scope/Type/Number.hpp>
#include <Language/AST/Scope/VariableScope.hpp>

namespace Language::Instruction
{
	bool Variable::exists() const
	{
		const auto& variableScope = dynamic_cast<const AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		return variableScope.variableExists(getName());
	}

	void Variable::setValue(std::unique_ptr<AST::Scope::Type::Value>&& value)
	{
		auto& variableScope = dynamic_cast<AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		variableScope.setVariable(getName(), std::move(value));
	}

	const std::unique_ptr<AST::Scope::Type::Value>& Variable::getValue() const
	{
		const auto& variableScope = dynamic_cast<const AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		return variableScope.getVariable(getName());
	}

	std::unique_ptr<AST::Instruction> Variable::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		auto variableName = parsingInformations.nextWord();
		if (variableName.empty())
			return nullptr;
		const auto& variableScope = dynamic_cast<const AST::Scope::VariableScope&>(scope.findScope(AST::Scope::VariableScopeType));
		if (!variableScope.variableSignatureExists(variableName))
			return nullptr;
		pos += variableName.length();

		parsingInformations.skipSpaces();

		CppUtils::Logger::logInformation(variableName, false);
		return std::make_unique<Variable>(std::move(variableName), &scope);
	}
	
	std::unique_ptr<AST::Scope::Type::Value> Variable::interpret()
	{
		const auto &variableScope = dynamic_cast<const AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		return variableScope.getVariable(getName())->cloneValue();
	}

	std::ostream& operator<<(std::ostream& os, const Variable& variable)
	{
		os << "Variable(" << variable.getName() << ')';
		return os;
	}
}
