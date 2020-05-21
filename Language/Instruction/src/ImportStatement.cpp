#include <Language/Instruction/ImportStatement.hpp>

namespace Language::Instruction
{
	ImportStatement::ImportStatement(): AST::Instruction{AST::InstructionType::IMPORTSTATEMENT}
	{}

	std::unique_ptr<AST::Instruction> ImportStatement::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		auto firstWord = parsingInformations.nextWord();
		if (firstWord != Keyword)
			return nullptr;
		parsingInformations.pos += firstWord.length();
		parsingInformations.skipSpaces();

		CppUtils::Logger::logInformation(std::string{Keyword} + " ", false);
		auto filenameString = Parser::parseString(parsingInformations);
		if (filenameString == nullptr)
			throw std::runtime_error{"Une valeur textuelle est attendue. Il manque une ouverture de guillemet ou d'apostrophe."};
		dynamic_cast<AST::Scope::FileScope&>(scope.findScope(AST::Scope::FileScopeType)).importDll(filenameString->getValue());
		return std::make_unique<ImportStatement>();
	}

	std::unique_ptr<AST::Scope::Type::Value> ImportStatement::interpret()
	{
		return std::make_unique<AST::Scope::Type::Number>();
	}
}
