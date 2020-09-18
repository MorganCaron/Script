#pragma once

#include <Language/Parser/Value/StringParser.hpp>
#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Namespace/ImportDeclaration.hpp>

namespace Language::Parser::Declaration
{
	inline std::unique_ptr<AST::Core::Instruction> parseImportDeclaration(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos, verbose] = cursor;

		if (!cursor.isKeywordSkipIt(AST::Namespace::ImportDeclaration::Keyword))
			return nullptr;
		cursor.skipSpaces();

		CppUtils::Log::Logger::logInformation(AST::Namespace::ImportDeclaration::Keyword.data() + " "s, false);
		auto filename = Value::parseQuote(cursor);
		if (filename.empty())
			throw std::runtime_error{"Une valeur textuelle est attendue. Il manque une ouverture de guillemet ou d'apostrophe."};
		cursor.parseSemicolon();
		
		auto fileScope = dynamic_cast<AST::Namespace::NamespaceScope&>(scope.findScope(AST::Namespace::NamespaceScopeType));
		fileScope.importDll(filename);
		return std::make_unique<AST::Namespace::ImportDeclaration>(&scope);
	}
}
