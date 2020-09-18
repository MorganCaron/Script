#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Object/Class.hpp>
#include <Language/Parser/Declaration/DeclarationParser.hpp>

namespace Language::Parser::Declaration
{
	inline std::unique_ptr<AST::Core::Instruction> parseClass(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos, verbose] = cursor;

		if (!cursor.isKeywordSkipIt(AST::Object::Class::Keyword))
			return nullptr;
		cursor.skipSpaces();

		auto className = cursor.getWordRequired("Le mot clef "s + AST::Object::Class::Keyword.data() + " doit etre suivi d un nom.");
		if (verbose)
		{
			CppUtils::Log::Logger::logInformation(AST::Object::Class::Keyword.data() + " "s, false);
			CppUtils::Log::Logger::logDetail(className);
		}
		cursor.skipSpaces();
		
		auto prototype = std::make_unique<AST::Object::Class>(std::move(className), &scope);
		auto prototypeParsingInformations = AST::ParsingTools::Cursor{*prototype, *prototype, src, pos, verbose};

		if (cursor.getChar() != '{')
			return nullptr;
		if (verbose)
			CppUtils::Log::Logger::logInformation("{");
		++pos;

		while (!cursor.isEndOfCode() && cursor.getChar() != '}')
		{
			prototype->addInstruction(parseDeclaration(prototypeParsingInformations));
			cursor.skipSpaces();
		}
		if (cursor.isEndOfCode())
			throw std::runtime_error{"Une accolade n est jamais fermee."};
		if (verbose)
			CppUtils::Log::Logger::logInformation("}", false);
		++pos;

		return prototype;
	}
}
