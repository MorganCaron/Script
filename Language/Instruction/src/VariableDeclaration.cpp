#include <Language/Instruction/VariableDeclaration.hpp>

#include <Language/AST/Scope/Type/Number.hpp>
#include <Language/AST/Scope/VariableScope.hpp>

namespace Language::Instruction
{
	bool VariableDeclaration::exists() const
	{
		const auto& variableScope = dynamic_cast<const AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		return variableScope.variableExists(getName());
	}

	void VariableDeclaration::declare(AST::Scope::Type::Variable&& variable)
	{
		auto& variableScope = dynamic_cast<AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		variableScope.declareVariable(getName(), std::move(variable));
	}

	void VariableDeclaration::setValue(std::unique_ptr<AST::Scope::Type::Value>&& value)
	{
		auto& variableScope = dynamic_cast<AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		variableScope.setVariableValue(getName(), std::move(value));
	}

	const std::unique_ptr<AST::Scope::Type::Value>& VariableDeclaration::getValue() const
	{
		const auto& variableScope = dynamic_cast<const AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		return variableScope.getVariable(getName()).value;
	}

	std::unique_ptr<AST::Instruction> VariableDeclaration::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		const auto firstWord = parsingInformations.nextWord();
		if (firstWord.empty())
			return nullptr;
		pos += firstWord.length();
		if (firstWord != "let" && firstWord != "const")
			return nullptr;
		const auto constant = (firstWord.at(0) == 'c');
		
		parsingInformations.skipSpaces();
		const auto secondWord = parsingInformations.nextWord();
		if (secondWord.empty())
			throw std::runtime_error{"Le mot clef " + firstWord + " doit etre suivi d'un nom de variable."};
		pos += secondWord.length();

		parsingInformations.skipSpaces();
		if (parsingInformations.currentChar() != '=')
			throw std::runtime_error{"Une déclaration de variable doit être suivie par l'affectation d'une valeur."};
		++pos;
		CppUtils::Logger::logInformation(firstWord + " " + secondWord + " = ", false);

		parsingInformations.skipSpaces();
		auto value = Parser::parseValue(parsingInformations);
		if (value == nullptr)
			throw std::runtime_error{"Vous devez renseigner une valeur lors de la déclaration d'une variable."};

		auto variable = AST::Scope::Type::Variable{value->interpret(), constant};
		return std::make_unique<VariableDeclaration>(std::move(secondWord), &scope, std::move(variable));
	}
	
	std::unique_ptr<AST::Scope::Type::Value> VariableDeclaration::interpret()
	{
		const auto &variableScope = dynamic_cast<const AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		return variableScope.getVariable(getName()).value->cloneValue();
	}

	std::ostream& operator<<(std::ostream& os, const VariableDeclaration& variable)
	{
		os << "Variable declaration: " << variable.getName();
		return os;
	}
}
