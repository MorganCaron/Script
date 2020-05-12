#include "Language/Bracket.hpp"

#include <Language/Scope/Type/Number.hpp>
#include "Language/AST.hpp"

namespace Language
{
	void Bracket::parse(ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;

		CppUtils::Logger::log(CppUtils::Logger::OutputType::Cout, CppUtils::Logger::MessageType::Information, "{");
		while (code[pos] != '}')
		{
			if (!AST::parseInstruction(*this, *this, parsingInformations))
				throw std::runtime_error{"Une accolade n'est jamais fermée."};
			AST::parseSpace(parsingInformations);
		}
		++pos;
		CppUtils::Logger::logWithoutNewLine(CppUtils::Logger::OutputType::Cout, CppUtils::Logger::MessageType::Information, "}");
	}

	std::unique_ptr<Scope::Type::Value> Bracket::interpret()
	{
		std::unique_ptr<Scope::Type::Value> result = std::make_unique<Scope::Type::Number>();

		CppUtils::Logger::log(CppUtils::Logger::OutputType::Cout, CppUtils::Logger::MessageType::Information, "{");
		for (auto& instruction : m_instructions)
			result = instruction->interpret();
		CppUtils::Logger::logWithoutNewLine(CppUtils::Logger::OutputType::Cout, CppUtils::Logger::MessageType::Information, "}");
		return result;
	}
}
