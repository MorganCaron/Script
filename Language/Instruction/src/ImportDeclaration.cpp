#include <Language/Instruction/ImportDeclaration.hpp>

namespace Language::Instruction
{
	std::unique_ptr<AST::Instruction> ImportDeclaration::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		auto keyword = parsingInformations.nextWord();
		if (keyword != Keyword)
			return nullptr;
		parsingInformations.pos += Keyword.length();
		parsingInformations.skipSpaces();

		CppUtils::Logger::logInformation(Keyword.data() + " "s, false);
		auto filenameString = Parser::parseString(parsingInformations);
		if (filenameString == nullptr)
			throw std::runtime_error{"Une valeur textuelle est attendue. Il manque une ouverture de guillemet ou d'apostrophe."};
		dynamic_cast<AST::Scope::FileScope&>(scope.findScope(AST::Scope::FileScopeType)).importDll(filenameString->getValue());
		return std::make_unique<ImportDeclaration>(&scope);
	}

	std::unique_ptr<AST::Scope::Type::Value> ImportDeclaration::interpret()
	{
		return std::make_unique<AST::Scope::Type::Number>();
	}
}
