#pragma once

#include <Language/Parser/Value/StringParser.hpp>
#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/File/ImportDeclaration.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseImportDeclaration(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos] = cursor;

		if (!cursor.isKeywordSkipIt(AST::File::ImportDeclaration::Keyword))
			return nullptr;
		cursor.skipSpaces();

		CppUtils::Logger::logInformation(AST::File::ImportDeclaration::Keyword.data() + " "s, false);
		auto filename = Value::parseQuote(cursor);
		if (filename.empty())
			throw std::runtime_error{"Une valeur textuelle est attendue. Il manque une ouverture de guillemet ou d'apostrophe."};
		
		auto fileScope = dynamic_cast<AST::File::FileScope&>(scope.findScope(AST::File::FileScopeType));
		fileScope.importDll(filename);
		return std::make_unique<AST::File::ImportDeclaration>(&scope);
	}
}
