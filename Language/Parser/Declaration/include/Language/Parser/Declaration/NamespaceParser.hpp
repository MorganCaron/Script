#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Namespace/NamespaceDeclaration.hpp>
#include <Language/Parser/Instruction/InstructionParser.hpp>

namespace Language::Parser::Declaration
{
	inline std::unique_ptr<AST::Core::Instruction> parseNamespace(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt(AST::Namespace::NamespaceDeclaration::Keyword))
			return nullptr;
		context.skipSpacesAndComments();

		auto namespaceName = cursor.getKeywordRequired("Le mot clef "s + AST::Namespace::NamespaceDeclaration::Keyword.data() + " doit etre suivi d un nom.");
		if (verbose)
			CppUtils::Log::Logger::logInformation(AST::Namespace::NamespaceDeclaration::Keyword.data() + " "s + namespaceName);
		context.skipSpacesAndComments();

		auto namespaceDeclaration = std::make_unique<AST::Namespace::NamespaceDeclaration>(std::move(namespaceName), &scope);
		auto namespaceParsingInformations = AST::ParsingTools::Context{*namespaceDeclaration, *namespaceDeclaration, cursor, verbose};

		if (cursor.getChar() != '{')
			return nullptr;
		if (verbose)
			CppUtils::Log::Logger::logInformation("{");
		++cursor.pos;

		while (!cursor.isEndOfString() && cursor.getChar() != '}')
		{
			namespaceDeclaration->addInstruction(parseDeclaration(namespaceParsingInformations));
			context.skipSpacesAndComments();
		}
		if (cursor.isEndOfString())
			throw std::runtime_error{"Une accolade n est jamais fermee."};
		if (verbose)
			CppUtils::Log::Logger::logInformation("}", false);
		++cursor.pos;

		return namespaceDeclaration;
	}
}
