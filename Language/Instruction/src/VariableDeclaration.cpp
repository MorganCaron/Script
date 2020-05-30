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

	void VariableDeclaration::declare(bool constant, std::unique_ptr<AST::Scope::Type::Value>&& value, std::string type)
	{
		auto& variableScope = dynamic_cast<AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType));
		auto variableSignature = AST::Scope::VariableScope::VariableSignature{constant, std::move(type)};
		variableScope.addVariableSignature(getName(), std::move(variableSignature));
		if (value != nullptr)
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
		CppUtils::Logger::logInformation(keyword + " " + variableName, false);
   
		parsingInformations.skipSpaces();
		auto typeName = std::string{};
		const auto typed = (parsingInformations.currentChar() == ':');
		if (typed)
		{
			++pos;
			parsingInformations.skipSpaces();
			typeName = parsingInformations.nextWord();
			if (typeName.empty())
				throw std::runtime_error{"Le nom d'un type est attendu."};
			pos += typeName.length();
			CppUtils::Logger::logInformation(": " + typeName, false);
		}

		parsingInformations.skipSpaces();
		auto value = std::unique_ptr<AST::Scope::Type::Value>(nullptr);
		const auto initialized = (parsingInformations.currentChar() == '=');
		if (initialized)
		{
			++pos;
			CppUtils::Logger::logInformation(" = ", false);
			parsingInformations.skipSpaces();
			auto valueInstruction = Parser::parseValue(parsingInformations);
			if (valueInstruction == nullptr)
				throw std::runtime_error{"Une valeur est attendue."};
			value = valueInstruction->interpret();
			if (typed && value->getType() != typeName)
				throw std::runtime_error{"La valeur ne correspond pas au type de la variable."};
		}

		if (typed && initialized)
			throw std::runtime_error{"Vous n avez pas besoin de préciser le type de la variable."};

		typeName = typed ? typeName : value->getType().data();
		return std::make_unique<VariableDeclaration>(std::move(variableName), &scope, constant, std::move(value), typeName);
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
