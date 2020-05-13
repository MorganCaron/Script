#include "Language/Bracket.hpp"

#include <Language/Scope/Type/Number.hpp>
#include "Language/AST.hpp"

namespace Language
{
	void Bracket::parse(ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;

		CppUtils::Logger::logInformation("{");
		while (code[pos] != '}')
		{
			if (!AST::parseInstruction(*this, *this, parsingInformations))
				throw std::runtime_error{"Une accolade n'est jamais fermée."};
			AST::parseSpace(parsingInformations);
		}
		++pos;
		CppUtils::Logger::logInformation("}", false);
	}

	std::unique_ptr<Scope::Type::Value> Bracket::interpret()
	{
		CppUtils::Logger::logInformation("{");
		for (auto& instruction : m_instructions)
		{
			auto result = instruction->interpret();
			if (instruction->getInstructionType() == InstructionType::RETURN)
				return result;
		}
		CppUtils::Logger::logInformation("}", false);
		return std::make_unique<Language::Scope::Type::Number>(0);
	}
}
