#include "Language/Variable.hpp"

#include <Language/Scope/Type/Number.hpp>
#include "Language/AST.hpp"

namespace Language
{
	bool Variable::exists() const
	{
		return dynamic_cast<const Scope::VariableScope&>(getScope().findScope(Scope::VariableScopeType)).variableExists(getName());
	}

	void Variable::setValue(std::unique_ptr<Scope::Type::Value>&& value)
	{
		dynamic_cast<Scope::VariableScope&>(getScope().findScope(Scope::VariableScopeType)).addVariable(getName(), std::move(value), m_local);
	}

	const std::unique_ptr<Scope::Type::Value>& Variable::getValue() const
	{
		return dynamic_cast<const Scope::VariableScope&>(getScope().findScope(Scope::VariableScopeType)).getVariable(getName());
	}

	std::unique_ptr<Scope::Type::Value> Variable::interpret()
	{
		const auto &variableScope = dynamic_cast<const Scope::VariableScope&>(getScope().findScope(Scope::VariableScopeType));
		if (!variableScope.variableExists(getName()))
			setValue(std::make_unique<Scope::Type::Number>());
		return variableScope.getVariable(getName())->cloneValue();
	}

	std::unique_ptr<Instruction> Variable::parse([[maybe_unused]] InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations, std::string word)
	{
		auto& [code, pos] = parsingInformations;
		static const auto words = std::vector<std::string>{ "var", "let", "local" };
		auto local = std::find(words.begin(), words.end(), word) != words.end();

		if (local)
		{
			AST::parseSpace(parsingInformations);
			if ((word = parsingInformations.nextWord()).empty())
				throw std::runtime_error("Le mot clef " + word + " doit etre suivi d'un nom de variable.");
			pos += word.length();
		}
		CppUtils::Logger::logWithoutNewLine(CppUtils::Logger::OutputType::Cout, CppUtils::Logger::MessageType::Information, word);
		return std::make_unique<Variable>(std::move(word), &scope, local);
	}

	std::ostream& operator<<(std::ostream& os, const Variable& variable)
	{
		os << "Variable(" << variable.getName() << ')';
		return os;
	}
}
