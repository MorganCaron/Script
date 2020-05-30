#include <Language/Instruction/FunctionDeclaration.hpp>

#include <Language/AST/Scope/Type/Number.hpp>
#include <Language/AST/Scope/FunctionScope.hpp>
#include <Language/Instruction/Bracket.hpp>

namespace Language::Instruction
{
	FunctionDeclaration::FunctionDeclaration(std::string name, AST::Scope::BaseScope* scope):
		CppUtils::Type::Named{std::move(name)},
		AST::Instruction{std::string{Type}},
		AST::Scope::VariableScope{scope}
	{}

	std::unique_ptr<AST::Scope::Type::ITFunction<std::unique_ptr<AST::Scope::Type::Value>(const AST::Scope::Type::Args&)>> FunctionDeclaration::cloneFunction() const
	{
		return std::make_unique<FunctionDeclaration>(*this);
	}

	void FunctionDeclaration::addArgument(std::string name, AST::Scope::VariableScope::VariableSignature&& signature)
	{
		addVariableSignature(name, std::move(signature));
		m_arguments.emplace_back(std::move(name));
	}

	std::unique_ptr<AST::Scope::Type::Value> FunctionDeclaration::operator()(const AST::Scope::Type::Args& arguments)
	{
		if (m_instructions.empty())
			throw std::runtime_error{"Une fonction ne contient aucune instruction."};
		auto& instruction = *m_instructions[0];
		auto& scope = dynamic_cast<AST::Scope::NormalScope&>(instruction);
		auto& variableScope = dynamic_cast<AST::Scope::VariableScope&>(scope.findScope(AST::Scope::VariableScopeType));
		variableScope.resetVariables();
		const auto nbArguments = m_arguments.size();
		const auto nbPassedArgument = arguments.size();
		if (nbArguments != nbPassedArgument)
			throw std::runtime_error{"Le nombre d argument est incorrect."};
		for (auto i = std::size_t{0}; i < nbArguments; ++i)
		{
			auto value = arguments[i]->cloneValue();
			const auto& argument = m_arguments[i];
			const auto& signature = variableScope.getVariableSignature(argument);
			if (value->getType() != signature.type)
				throw std::runtime_error{"L argument doit etre de type "s + signature.type + ". Vous ne pouvez pas lui affecter une valeur de type " + value->getType().data()};
			variableScope.setVariable(argument, std::move(value));
		}
		return instruction.interpret();
	}

	std::unique_ptr<AST::Instruction> FunctionDeclaration::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		auto keyword = parsingInformations.nextWord();
		if (keyword != Keyword)
			return nullptr;
		pos += Keyword.length();
		parsingInformations.skipSpaces();

		auto functionName = parsingInformations.nextWord();
		if (functionName.empty())
			throw std::runtime_error{"Le mot clef function doit etre suivi d un nom de fonction."};
		pos += functionName.size();
		parsingInformations.skipSpaces();

		if (src.at(pos) != '(')
			throw std::runtime_error{"La declaration d une fonction doit avoir des parentheses."};
		++pos;

		auto functionDeclaration = std::make_unique<FunctionDeclaration>(std::move(functionName), &scope);
		auto functionStatementParserInformations = Parser::ParsingInformations{*functionDeclaration, *functionDeclaration, src, pos};
		CppUtils::Logger::logInformation(Keyword.data() + " "s + functionDeclaration->getName().data() + '(', false);
		
		parsingInformations.skipSpaces();
		if (parsingInformations.currentChar() != ')')
		{
			auto loop = true;
			do
			{
				parsingInformations.skipSpaces();
				auto keyword = parsingInformations.nextWord();
				if (keyword.empty())
					return nullptr;
				pos += keyword.length();
				if (keyword != "let" && keyword != "const")
					return nullptr;
				auto constant = (keyword == "const");
				
				parsingInformations.skipSpaces();
				auto argumentName = parsingInformations.nextWord();
				if (argumentName.empty())
					throw std::runtime_error{"Une variable est attendue."};
				pos += argumentName.size();
				
				parsingInformations.skipSpaces();
				if (parsingInformations.currentChar() != ':')
					throw std::runtime_error{"Le type de l argument doit etre renseigne."};
				++pos;

				parsingInformations.skipSpaces();
				auto typeName = parsingInformations.nextWord();
				if (typeName.empty())
					throw std::runtime_error{"Le nom d'un type est attendu."};
				pos += typeName.size();
				
				CppUtils::Logger::logInformation(keyword + " " + argumentName + ": " + typeName, false);
				auto signature = AST::Scope::VariableScope::VariableSignature{constant, std::move(typeName)};
				functionDeclaration->addArgument(std::move(argumentName), std::move(signature));
				
				parsingInformations.skipSpaces();
				loop = (parsingInformations.currentChar() == ',');
				if (loop)
				{
					CppUtils::Logger::logInformation(", ", false);
					++pos;
				}
			}
			while (loop);
			if (parsingInformations.currentChar() != ')')
				throw std::runtime_error{"Vous avez probablement oublie de fermer les parentheses d une fonction."};
		}
		++parsingInformations.pos;
		CppUtils::Logger::logInformation(")");
		
		auto instruction = Parser::parseInstruction(functionStatementParserInformations);
		if (!instruction)
			throw std::runtime_error{"Une instruction est requise dans la declaration de la fonction."};
		functionDeclaration->addInstruction(std::move(instruction));
		return functionDeclaration;
	}

	std::unique_ptr<AST::Scope::Type::Value> FunctionDeclaration::interpret()
	{
		CppUtils::Logger::logInformation("Declare "s + Keyword.data() + " " + getName().data() + "(", false);
		auto& functionScope = dynamic_cast<AST::Scope::FunctionScope&>(getScope().findScope(AST::Scope::FunctionScopeType));
		functionScope.addFunction(getName(), std::make_unique<FunctionDeclaration>(*this));
		CppUtils::Logger::logInformation(")");
		return std::make_unique<AST::Scope::Type::Number>();
	}

	std::ostream& operator<<(std::ostream& os, const FunctionDeclaration& functionDeclaration)
	{
		os << "Function declaration: " << functionDeclaration.getName();
		return os;
	}
}
