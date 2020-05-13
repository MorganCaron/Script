#include "Language/AST.hpp"

#include "Language/Bracket.hpp"
#include "Language/FunctionStatement.hpp"
#include "Language/ControlStructure.hpp"
#include "Language/Object.hpp"
#include "Language/Operator.hpp"
#include "Language/Value.hpp"
#include "Language/Return.hpp"

namespace Language
{
	AST::AST(std::string code)
	{
		parse(std::move(code));
	}

	void AST::parse(std::string code)
	{
		auto parsingInformations = ParsingInformations{std::move(code), 0};
		auto& pos = parsingInformations.pos;
		const auto length = parsingInformations.code.length();

		CppUtils::Logger::logInformation("#- PARSER_/");
		while (pos < length)
		{
			if (!parseInstruction(*this, *this, parsingInformations))
				throw std::runtime_error{"Caractere inconnu."};
			parseSpace(parsingInformations);
		}
	}

	void AST::interpret()
	{
		CppUtils::Logger::logInformation("#- INTERPRETER_/");
		for (auto& instruction : m_instructions)
			static_cast<void>(instruction->interpret());
	}

	bool AST::parseInstruction(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;
		auto length = code.length();
		static const auto controlStructureWords = std::vector<std::string>{"if", "then", "while", "else", "do", "switch", "case", "repeat", "break", "for"};

		parseSpace(parsingInformations);
		if (parsingInformations.currentChar() == '{')
		{
			auto bracket = std::make_unique<Bracket>(&scope);
			++pos;
			bracket->parse(parsingInformations);
			container.addInstruction(std::move(bracket));
			return true;
		}
		else if (std::string(AlphaChar).find(parsingInformations.currentChar()) != std::string::npos)
		{
			auto word = parsingInformations.nextWord();
			if (word == Keyword::FunctionStatement)
			{
				pos += word.length();
				parseSpace(parsingInformations);
				FunctionStatement::parse(container, scope, parsingInformations);
			}
			else if (word == Keyword::ImportStatement)
			{
				pos += word.length();
				parseSpace(parsingInformations);
				AST::parseImport(container, scope, parsingInformations);
			}
			else if (std::find(controlStructureWords.begin(), controlStructureWords.end(), word) != controlStructureWords.end())
			{
				pos += word.length();
				parseSpace(parsingInformations);
				auto controlStructure = std::make_unique<ControlStructure>(word, &scope);
				controlStructure->parse(parsingInformations);
				container.addInstruction(std::move(controlStructure));
			}
			else if (word == Keyword::ObjectStatement)
			{
				pos += word.length();
				parseSpace(parsingInformations);
				Object::parse(container, scope, parsingInformations);
			}
			else if (word == Keyword::ReturnStatement)
			{
				pos += word.length();
				parseReturn(container, scope, parsingInformations);
			}
			else
				container.addInstruction(Operator::parseOperation(container, scope, parsingInformations));
		}
		else
			throw std::runtime_error{"Erreur de syntaxe. Une instruction est attendue."};
		std::cout << std::endl;
		if (parsingInformations.currentChar() == ';')
			++pos;
		else if (Keyword::SemicolonRequired)
			throw std::runtime_error{"Erreur de syntaxe. Un point-virgule est attendu à la fin des instructions."};
		return (pos < length);
	}

	bool AST::parseCommentary(ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;
		
		if (parsingInformations.currentChar() == '/' && parsingInformations.nextChar() == '/')
		{
			pos += 2;
			while (pos < code.size() && parsingInformations.currentChar() != '\n')
				++pos;
			if (parsingInformations.currentChar() == '\n')
				++pos;
			return true;
		}
		if (parsingInformations.currentChar() == '/' && parsingInformations.nextChar() == '*')
		{
			pos += 2;
			while (pos + 1 < code.size() && (parsingInformations.currentChar() != '*' || parsingInformations.nextChar() != '/'))
				++pos;
			if (pos + 1 == code.size())
				throw std::runtime_error{"Commentaire jamais ferme."};
			else
				pos += 2;
			return true;
		}
		return false;
	}

	void AST::parseSpace(ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;
		auto length = code.length();

		do
		{
			while (pos < length && std::string(SpaceChar).find(parsingInformations.currentChar()) != std::string::npos)
				++pos;
		} while (pos < length && parseCommentary(parsingInformations));
	}

	void AST::parseImport(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations)
	{
		CppUtils::Logger::logInformation(std::string{Keyword::ImportStatement} + " ", false);
		auto filename = Value::parseString(container, parsingInformations)->getValue();
		auto dotPosition = filename.find_last_of('.');
		auto filenameWithoutExt = filename.substr(0, dotPosition);
		auto ext = filename.substr(dotPosition);
		if (ext == ".dll")
			dynamic_cast<Scope::FileScope&>(scope.findScope(Scope::FileScopeType)).importDll(filenameWithoutExt);
		else
			throw std::runtime_error{"Importation du fichier " + filename + ext + " impossible. Extension " + ext + " inconnue."};
	}

	void AST::parseReturn(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations)
	{
		CppUtils::Logger::logInformation(std::string{Keyword::ReturnStatement} + " ", false);
		parseSpace(parsingInformations);
		auto returnStatement = std::make_unique<Return>();
		returnStatement->addInstruction(Operator::parseOperation(container, scope, parsingInformations));
		container.addInstruction(std::move(returnStatement));
	}
}
