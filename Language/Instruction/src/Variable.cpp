#include <Language/Instruction/Variable.hpp>

#include <Language/AST/Scope/Type/Number.hpp>
#include <Language/AST/Scope/VariableScope.hpp>

namespace Language::Instruction
{
	bool Variable::exists() const
	{
		return dynamic_cast<const AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType)).variableExists(getName());
	}

	void Variable::setValue(std::unique_ptr<AST::Scope::Type::Value>&& value)
	{
		dynamic_cast<AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType)).addVariable(getName(), std::move(value), m_local);
	}

	const std::unique_ptr<AST::Scope::Type::Value>& Variable::getValue() const
	{
		return dynamic_cast<const AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType)).getVariable(getName());
	}

	std::unique_ptr<AST::Instruction> Variable::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		auto local = false;
		auto firstWord = parsingInformations.nextWord();
		if (firstWord.empty())
			return nullptr;
		pos += firstWord.length();
		if (firstWord == "var" || firstWord == "const")
			local = true;

		parsingInformations.skipSpaces();
		auto secondWord = std::string{};
		if (local)
		{
			if ((secondWord = parsingInformations.nextWord()).empty())
				throw std::runtime_error{"Le mot clef " + firstWord + " doit etre suivi d'un nom de variable."};
			pos += secondWord.length();
		}

		CppUtils::Logger::logInformation(firstWord + (local ? (" " + secondWord) : ""), false);
		return std::make_unique<Variable>(std::move(local ? secondWord : firstWord), &scope, local);
	}
	
	std::unique_ptr<AST::Scope::Type::Value> Variable::interpret()
	{
		const auto &variableScope = dynamic_cast<const AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		if (!variableScope.variableExists(getName()))
			setValue(std::make_unique<AST::Scope::Type::Number>());
		return variableScope.getVariable(getName())->cloneValue();
	}

	std::ostream& operator<<(std::ostream& os, const Variable& variable)
	{
		os << "Variable(" << variable.getName() << ')';
		return os;
	}
}
