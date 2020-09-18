#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Namespace/NamespaceDeclaration.hpp>
#include <Language/Parser/Instruction/InstructionParser.hpp>

namespace Language::Parser::Declaration
{
	inline std::unique_ptr<AST::Core::Instruction> parseNamespace(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos, verbose] = cursor;

		if (!cursor.isKeywordSkipIt(AST::Namespace::NamespaceDeclaration::Keyword))
			return nullptr;
		cursor.skipSpaces();

		auto namespaceName = cursor.getWordRequired("Le mot clef "s + AST::Namespace::NamespaceDeclaration::Keyword.data() + " doit etre suivi d un nom.");
		if (verbose)
			CppUtils::Log::Logger::logInformation(AST::Namespace::NamespaceDeclaration::Keyword.data() + " "s + namespaceName);
		cursor.skipSpaces();

		auto namespaceDeclaration = std::make_unique<AST::Namespace::NamespaceDeclaration>(std::move(namespaceName), &scope);
		auto namespaceParsingInformations = AST::ParsingTools::Cursor{*namespaceDeclaration, *namespaceDeclaration, src, pos, verbose};

		if (cursor.getChar() != '{')
			return nullptr;
		if (verbose)
			CppUtils::Log::Logger::logInformation("{");
		++pos;

		while (!cursor.isEndOfCode() && cursor.getChar() != '}')
		{
			namespaceDeclaration->addInstruction(parseDeclaration(namespaceParsingInformations));
			cursor.skipSpaces();
		}
		if (cursor.isEndOfCode())
			throw std::runtime_error{"Une accolade n est jamais fermee."};
		if (verbose)
			CppUtils::Log::Logger::logInformation("}", false);
		++pos;

		return namespaceDeclaration;
	}
}
