#include <Language/Parser/Parser.hpp>

#include <Language/AST/Scope/BaseScope.hpp>
#include <Language/AST/Scope/LanguageScope.hpp>

namespace Language::Parser
{
	std::string ParsingInformations::nextWord() const
	{
		auto wordLength = std::size_t{0};

		if (std::string{AlphaChar}.find(src.at(pos + wordLength)) != std::string::npos)
		{
			do
				++wordLength;
			while (std::string{AlphaNumChar}.find(src.at(pos + wordLength)) != std::string::npos);
		}
		return src.substr(pos, wordLength);
	}

	bool ParsingInformations::parseCommentary()
	{
		if (currentChar() == '/' && nextChar() == '/')
		{
			pos += 2;
			while (pos < src.size() && currentChar() != '\n')
				++pos;
			if (currentChar() == '\n')
				++pos;
			return true;
		}
		if (currentChar() == '/' && nextChar() == '*')
		{
			pos += 2;
			while (pos + 1 < src.size() && (currentChar() != '*' || nextChar() != '/'))
				++pos;
			if (pos + 1 == src.size())
				throw std::runtime_error{"Commentaire jamais ferme."};
			else
				pos += 2;
			return true;
		}
		return false;
	}

	void ParsingInformations::skipSpaces()
	{
		auto length = src.length();

		do
		{
			while (pos < length && std::string(SpaceChar).find(currentChar()) != std::string::npos)
				++pos;
		} while (pos < length && parseCommentary());
	}
	
	std::unique_ptr<AST::Instruction> parseInstruction(ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		parsingInformations.skipSpaces();
		const auto& languageScope = dynamic_cast<const AST::Scope::LanguageScope&>(scope.findScope(AST::Scope::LanguageScopeType));
		const auto& instructionParsers = languageScope.getInstructionParsers();
		for (const auto& instructionParser : instructionParsers)
		{
			auto startPos = pos;
			auto instruction = instructionParser.second(parsingInformations);
			if (instruction)
			{
				if (!parsingInformations.endOfCode() && parsingInformations.currentChar() == ';')
					++pos;
				CppUtils::Logger::logDebug(" -> " + instructionParser.first + " parser: " + instruction->getInstructionType());
				return instruction;
			}
			pos = startPos;
		}
		return nullptr;
	}

	std::unique_ptr<AST::Instruction> parseValue(ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		parsingInformations.skipSpaces();
		const auto& languageScope = dynamic_cast<const AST::Scope::LanguageScope&>(scope.findScope(AST::Scope::LanguageScopeType));
		const auto& valueParsers = languageScope.getValueParsers();
		for (const auto& valueParser : valueParsers)
		{
			auto startPos = pos;
			auto instruction = valueParser.second(parsingInformations);
			if (instruction)
				return parseOperator(parsingInformations, std::move(instruction));
			pos = startPos;
		}
		return nullptr;
	}

	std::unique_ptr<AST::Instruction> parseOperator(ParsingInformations& parsingInformations, std::unique_ptr<AST::Instruction>&& operand0)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		parsingInformations.skipSpaces();
		const auto& languageScope = dynamic_cast<const AST::Scope::LanguageScope&>(scope.findScope(AST::Scope::LanguageScopeType));
		const auto& operatorParsers = languageScope.getOperatorParsers();
		for (const auto& operatorParser : operatorParsers)
		{
			auto startPos = pos;
			operand0 = operatorParser.second(parsingInformations, std::move(operand0));
			if (pos != startPos)
				return std::move(operand0);
			pos = startPos;
		}
		return std::move(operand0);
	}
}
