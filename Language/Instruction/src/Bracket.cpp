#include <Language/Instruction/Bracket.hpp>

#include <Language/AST/Scope/Type/Number.hpp>

namespace Language::Instruction
{
	std::unique_ptr<AST::Instruction> Bracket::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		if (parsingInformations.currentChar() != '{')
			return nullptr;
		
		auto bracket = std::make_unique<Bracket>(&scope);
		auto bracketParsingInformations = Parser::ParsingInformations{*bracket, *bracket, src, ++pos};
		CppUtils::Logger::logInformation("{");
		
		while (!parsingInformations.endOfCode() && parsingInformations.currentChar() != '}')
		{
			auto instruction = Parser::parseInstruction(bracketParsingInformations);
			parsingInformations.skipSpaces();
			if (instruction != nullptr)
				bracket->addInstruction(std::move(instruction));
			else if (parsingInformations.currentChar() != '}')
				throw std::runtime_error{"Erreur de syntaxe. La chaine ne correspond à aucune instruction connue."};
		}

		if (parsingInformations.endOfCode() || parsingInformations.currentChar() != '}')
			throw std::runtime_error{"Une accolade n'est jamais fermée."};
		++pos;
		CppUtils::Logger::logInformation("}", false);

		return bracket;
	}

	std::unique_ptr<AST::Scope::Type::Value> Bracket::interpret()
	{
		CppUtils::Logger::logInformation("{");
		for (auto& instruction : m_instructions)
		{
			auto result = instruction->interpret();
			if (instruction->getInstructionType() == AST::InstructionType::RETURN)
			{
				CppUtils::Logger::logInformation("}", false);
				return result;
			}
		}
		CppUtils::Logger::logInformation("}", false);
		return std::make_unique<AST::Scope::Type::Number>(0);
	}
}
