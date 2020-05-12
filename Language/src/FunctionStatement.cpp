#include "Language/FunctionStatement.hpp"

#include <Language/Scope/Type/Number.hpp>
#include "Language/AST.hpp"
#include "Language/Bracket.hpp"

namespace Language
{
	FunctionStatement::FunctionStatement(std::string name, Language::Scope::BaseScope* scope):
		CppUtils::Type::Named{std::move(name)},
		Instruction{eInstructionType::FUNCTIONSTATEMENT},
		VariableScope{scope}
	{}

	std::unique_ptr<Scope::Type::ITFunction<std::unique_ptr<Scope::Type::Value>(const Scope::Type::Args&)>> FunctionStatement::cloneFunction() const
	{
		return std::make_unique<FunctionStatement>(*this);
	}

	void FunctionStatement::parse(ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;
		auto loop = true;
		auto word = std::string{};

		CppUtils::Logger::logWithoutNewLine(CppUtils::Logger::OutputType::Cout, CppUtils::Logger::MessageType::Information, "function "s + getName().data() + '(');
		AST::parseSpace(parsingInformations);
		if (parsingInformations.currentChar() != ')')
		{
			while (loop)
			{
				AST::parseSpace(parsingInformations);
				if ((word = parsingInformations.nextWord()).empty())
					throw std::runtime_error{"Une variable est attendue."};
				pos += word.size();
				m_args.emplace_back(std::move(word));
				AST::parseSpace(parsingInformations);
				if ((loop = (parsingInformations.currentChar() == ',')))
					++pos;
			}
			if (parsingInformations.currentChar() != ')')
				throw std::runtime_error{"Vous avez oublie de fermer les parentheses d une fonction."};
		}
		++pos;
		CppUtils::Logger::logWithoutNewLine(CppUtils::Logger::OutputType::Cout, CppUtils::Logger::MessageType::Information, ") ");
		if (!AST::parseInstruction(*this, *this, parsingInformations))
			throw std::runtime_error{"Une instruction est requise dans la declaration de la fonction."};
	}

	std::unique_ptr<Scope::Type::Value> FunctionStatement::interpret()
	{
		dynamic_cast<Scope::FunctionScope&>(getScope().findScope(Scope::FunctionScopeType)).addFunction(getName(), std::make_unique<FunctionStatement>(*this));
		return std::make_unique<Scope::Type::Number>();
	}

	std::unique_ptr<Scope::Type::Value> FunctionStatement::operator()(const Scope::Type::Args& arguments)
	{
		std::size_t i, size_names, size_values;

		if (m_instructions.empty())
			throw std::runtime_error("Une fonction ne contient aucune instruction.");
		auto& bracket = dynamic_cast<Bracket&>(*m_instructions[0]); 
		bracket.resetVariables();
		size_names = m_args.size();
		size_values = arguments.size();
		for (i = 0; i < size_names; ++i)
			bracket.addVariable(m_args[i], (i < size_values)? arguments[i]->cloneValue() : std::make_unique<Scope::Type::Number>(), true);
		return bracket.interpret();
	}

	void FunctionStatement::parse(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;
		auto word = parsingInformations.nextWord();

		if (word.empty())
			throw std::runtime_error("Le mot clef function doit etre suivi d un nom de fonction.");
		pos += word.size();
		AST::parseSpace(parsingInformations);
		if (code.at(pos) != '(')
			throw std::runtime_error("La declaration d une fonction doit avoir des parentheses.");
		auto functionStatement = std::make_unique<FunctionStatement>(std::move(word), &scope);
		++pos;
		functionStatement->parse(parsingInformations);
		container.addInstruction(std::move(functionStatement));
	}

	std::ostream& operator<<(std::ostream& os, const FunctionStatement& functionStatement)
	{
		os << "Function Statement: " << functionStatement.getName();
		return os;
	}
}
