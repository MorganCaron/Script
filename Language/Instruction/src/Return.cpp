#include <Language/Instruction/Return.hpp>

#include <Language/Instruction/Operator.hpp>

namespace Language::Instruction
{
	std::unique_ptr<AST::Instruction> Return::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		auto keyword = parsingInformations.nextWord();
		if (keyword != Keyword)
			return std::unique_ptr<Instruction>{nullptr};
		pos += Keyword.length();
		CppUtils::Logger::logInformation(std::string{keyword} + " ", false);

		parsingInformations.skipSpaces();
		auto returnStatement = std::make_unique<Return>(&scope);
		auto value = Parser::parseValue(parsingInformations);
		if (value == nullptr)
			throw std::runtime_error{"Le mot clef return doit etre suivi d une expression qui retourne une valeur."};
		returnStatement->addInstruction(std::move(value));
		return returnStatement;
	}

	std::unique_ptr<AST::Scope::Type::Value> Return::interpret()
	{
		return m_instructions.at(0)->interpret();
	}
}
