#pragma once

#include <Language/Parser/Value/StringParser.hpp>
#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Namespace/ImportDeclaration.hpp>

namespace Language::Parser::Declaration
{
	inline std::unique_ptr<AST::Core::Instruction> parseImportDeclaration(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt(AST::Namespace::ImportDeclaration::Keyword))
			return nullptr;
		context.skipSpacesAndComments();

		CppUtils::Log::Logger::logInformation(AST::Namespace::ImportDeclaration::Keyword.data() + " "s, false);
		auto filename = Value::parseQuote(context);
		if (filename.empty())
			throw std::runtime_error{"Une valeur textuelle est attendue. Il manque une ouverture de guillemet ou d'apostrophe."};
		context.parseSemicolon();
		
		auto& namespaceScope = scope.findScope<AST::Namespace::NamespaceScope>();
		namespaceScope.importDll(filename);
		return std::make_unique<AST::Namespace::ImportDeclaration>(&scope);
	}
}
