#include <Language/Instruction/FunctionStatement.hpp>

#include <Language/AST/Scope/Type/Number.hpp>
#include <Language/AST/Scope/FunctionScope.hpp>
#include <Language/Instruction/Bracket.hpp>

namespace Language::Instruction
{
	FunctionStatement::FunctionStatement(std::string name, AST::Scope::BaseScope* scope):
		CppUtils::Type::Named{std::move(name)},
		AST::Instruction{AST::InstructionType::FUNCTIONSTATEMENT},
		AST::Scope::VariableScope{scope}
	{}

	std::unique_ptr<AST::Scope::Type::ITFunction<std::unique_ptr<AST::Scope::Type::Value>(const AST::Scope::Type::Args&)>> FunctionStatement::cloneFunction() const
	{
		return std::make_unique<FunctionStatement>(*this);
	}

	void FunctionStatement::addArgument(std::string argumentName)
	{
		m_argumentNames.emplace_back(argumentName);
	}

	std::unique_ptr<AST::Scope::Type::Value> FunctionStatement::operator()(const AST::Scope::Type::Args& arguments)
	{
		if (m_instructions.empty())
			throw std::runtime_error("Une fonction ne contient aucune instruction.");
		auto& bracket = dynamic_cast<Bracket&>(*m_instructions[0]); 
		bracket.resetVariables();
		auto nbArgumentNames = m_argumentNames.size();
		auto nbPassedArgument = arguments.size();
		for (auto i = std::size_t{0}; i < nbArgumentNames; ++i)
			bracket.addVariable(m_argumentNames[i], (i < nbPassedArgument)? arguments[i]->cloneValue() : std::make_unique<AST::Scope::Type::Number>(), true);
		return bracket.interpret();
	}

	std::unique_ptr<AST::Instruction> FunctionStatement::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		auto firstWord = parsingInformations.nextWord();
		if (firstWord != Keyword)
			return nullptr;
		pos += firstWord.length();
		parsingInformations.skipSpaces();

		auto secondWord = parsingInformations.nextWord();
		if (secondWord.empty())
			throw std::runtime_error{"Le mot clef function doit etre suivi d un nom de fonction."};
		pos += secondWord.size();
		parsingInformations.skipSpaces();

		if (src.at(pos) != '(')
			throw std::runtime_error{"La declaration d une fonction doit avoir des parentheses."};
		++pos;

		auto functionStatement = std::make_unique<FunctionStatement>(std::move(secondWord), &scope);
		auto functionStatementParserInformations = Parser::ParsingInformations{*functionStatement, *functionStatement, src, pos};
		CppUtils::Logger::logInformation("function "s + functionStatement->getName().data() + '(', false);
		
		parsingInformations.skipSpaces();
		if (parsingInformations.currentChar() != ')')
		{
			auto word = std::string{};
			auto loop = true;
			do
			{
				parsingInformations.skipSpaces();
				if ((word = parsingInformations.nextWord()).empty())
					throw std::runtime_error{"Une variable est attendue."};
				parsingInformations.pos += word.size();
				functionStatement->addArgument(std::move(word));
				parsingInformations.skipSpaces();
				if ((loop = (parsingInformations.currentChar() == ',')))
					++pos;
			}
			while (loop);
			if (parsingInformations.currentChar() != ')')
				throw std::runtime_error{"Vous avez oublie de fermer les parentheses d une fonction."};
		}
		++parsingInformations.pos;
		CppUtils::Logger::logInformation(")");
		
		auto instruction = Parser::parseInstruction(functionStatementParserInformations);
		if (!instruction)
			throw std::runtime_error{"Une instruction est requise dans la declaration de la fonction."};
		functionStatement->addInstruction(std::move(instruction));
		return functionStatement;
	}

	std::unique_ptr<AST::Scope::Type::Value> FunctionStatement::interpret()
	{
		dynamic_cast<AST::Scope::FunctionScope&>(getScope().findScope(AST::Scope::FunctionScopeType)).addFunction(getName(), std::make_unique<FunctionStatement>(*this));
		return std::make_unique<AST::Scope::Type::Number>();
	}

	std::ostream& operator<<(std::ostream& os, const FunctionStatement& functionStatement)
	{
		os << "Function Statement: " << functionStatement.getName();
		return os;
	}
}
