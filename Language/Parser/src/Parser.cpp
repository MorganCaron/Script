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
		auto instruction = std::unique_ptr<AST::Instruction>{nullptr};
		const auto& instructionParsers = dynamic_cast<const AST::Scope::LanguageScope&>(scope.findScope(AST::Scope::LanguageScopeType)).getInstructionParsers();
		auto instructionParserIterator = instructionParsers.begin();
		while (instruction == nullptr && instructionParserIterator != instructionParsers.end())
		{
			auto startPos = pos;
			instruction = instructionParserIterator->second(parsingInformations);
			if (!instruction)
				pos = startPos;
			++instructionParserIterator;
		}
		if (parsingInformations.currentChar() == ';')
			++pos;
		if (instruction)
			std::cout << std::endl;
		return instruction;
	}

	std::unique_ptr<AST::Instruction> parseValue(ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		parsingInformations.skipSpaces();
		auto instruction = std::unique_ptr<AST::Instruction>{nullptr};
		const auto& valueParsers = dynamic_cast<const AST::Scope::LanguageScope&>(scope.findScope(AST::Scope::LanguageScopeType)).getValueParsers();
		auto valueParserIterator = valueParsers.begin();
		while (instruction == nullptr && valueParserIterator != valueParsers.end())
		{
			auto startPos = pos;
			instruction = valueParserIterator->second(parsingInformations);
			if (!instruction)
				pos = startPos;
			++valueParserIterator;
		}
		return instruction;
	}
}
