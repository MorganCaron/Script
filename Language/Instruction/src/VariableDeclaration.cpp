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

	void VariableDeclaration::declare(std::unique_ptr<AST::Scope::Type::Value>&& value, bool constant)
	{
		auto& variableScope = dynamic_cast<AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		auto variableSignature = AST::Scope::VariableScope::VariableSignature{constant, value->getType().data()};
		variableScope.addVariableSignature(getName(), std::move(variableSignature));
		variableScope.setVariable(getName(), std::move(value));
	}

	void VariableDeclaration::setValue(std::unique_ptr<AST::Scope::Type::Value>&& value)
	{
		auto& variableScope = dynamic_cast<AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		variableScope.setVariable(getName(), std::move(value));
	}

	const std::unique_ptr<AST::Scope::Type::Value>& VariableDeclaration::getValue() const
	{
		const auto& variableScope = dynamic_cast<const AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		return variableScope.getVariable(getName());
	}

	std::unique_ptr<AST::Instruction> VariableDeclaration::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		auto keyword = parsingInformations.nextWord();
		if (keyword.empty())
			return nullptr;
		pos += keyword.length();
		if (keyword != "let" && keyword != "const")
			return nullptr;
		const auto constant = (keyword == "const");
		
		parsingInformations.skipSpaces();
		auto variableName = parsingInformations.nextWord();
		if (variableName.empty())
			throw std::runtime_error{"Le mot clef " + keyword + " doit etre suivi d'un nom de variable."};
		pos += variableName.length();

		parsingInformations.skipSpaces();
		if (parsingInformations.currentChar() != '=')
			throw std::runtime_error{"Une declaration de variable doit etre suivie par l affectation d'une valeur."};
		++pos;
		CppUtils::Logger::logInformation(keyword + " " + variableName + " = ", false);

		parsingInformations.skipSpaces();
		auto value = Parser::parseValue(parsingInformations);
		if (value == nullptr)
			throw std::runtime_error{"Vous devez renseigner une valeur lors de la declaration d'une variable."};
		return std::make_unique<VariableDeclaration>(std::move(variableName), &scope, value->interpret(), constant);
	}
	
	std::unique_ptr<AST::Scope::Type::Value> VariableDeclaration::interpret()
	{
		const auto &variableScope = dynamic_cast<const AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		return variableScope.getVariable(getName())->cloneValue();
	}

	std::ostream& operator<<(std::ostream& os, const VariableDeclaration& variable)
	{
		os << "Variable declaration: " << variable.getName();
		return os;
	}
}
