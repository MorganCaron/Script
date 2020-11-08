#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Object/Class.hpp>
#include <Language/Parser/Declaration/DeclarationParser.hpp>

namespace Language::Parser::Declaration
{
	[[nodiscard]] inline std::unique_ptr<AST::Core::Instruction> parseClass(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt(AST::Object::Class::Keyword))
			return nullptr;
		context.skipSpacesAndComments();

		auto className = cursor.getKeywordRequired("Le mot clef "s + AST::Object::Class::Keyword.data() + " doit etre suivi d un nom.");
		if (verbose)
		{
			CppUtils::Log::Logger::logInformation(AST::Object::Class::Keyword.data() + " "s, false);
			CppUtils::Log::Logger::logDetail(className);
		}
		context.skipSpacesAndComments();
		
		auto prototype = std::make_unique<AST::Object::Class>(std::move(className), &scope);
		auto prototypeParsingInformations = AST::ParsingTools::Context{*prototype, *prototype, cursor, verbose};

		if (cursor.getChar() != '{')
			return nullptr;
		if (verbose)
			CppUtils::Log::Logger::logInformation("{");
		++cursor.pos;

		while (!cursor.isEndOfString() && cursor.getChar() != '}')
		{
			auto declaration = parseDeclaration(prototypeParsingInformations);
			declaration->indexe();
			prototype->addInstruction(std::move(declaration));
			context.skipSpacesAndComments();
		}
		if (cursor.isEndOfString())
			throw std::runtime_error{"Une accolade n est jamais fermee."};
		if (verbose)
			CppUtils::Log::Logger::logInformation("}", false);
		++cursor.pos;
		
		return prototype;
	}
}
