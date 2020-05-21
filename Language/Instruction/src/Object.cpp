#include <Language/Instruction/Object.hpp>

#include <Language/AST/Scope/ObjectScope.hpp>
#include <Language/Instruction/FunctionStatement.hpp>

namespace Language::Instruction
{
	Object::Object(Object const &src):
		AST::Scope::Type::Object{src},
		AST::Instruction{src},
		AST::InstructionContainer{src}
	{
		for (const std::pair<const std::string, std::unique_ptr<AST::Scope::FunctionType>>& pair : getFunctions())
			addFunction(pair.first, std::make_unique<FunctionStatement>(static_cast<const FunctionStatement&>(*pair.second)));
	}

	Object &Object::operator=(Object const &rhs)
	{
		AST::Scope::Type::Object::operator=(rhs);
		AST::Instruction::operator=(rhs);
		AST::InstructionContainer::operator=(rhs);
		for (const std::pair<const std::string, std::unique_ptr<AST::Scope::FunctionType>>& pair : getFunctions())
			addFunction(pair.first, std::make_unique<FunctionStatement>(static_cast<const FunctionStatement&>(*pair.second)));
		return *this;
	}

	std::unique_ptr<AST::Instruction> Object::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		auto firstWord = parsingInformations.nextWord();
		if (firstWord != Keyword)
			return std::unique_ptr<Instruction>{nullptr};
		pos += firstWord.length();
		parsingInformations.skipSpaces();

		auto secondWord = parsingInformations.nextWord();
		if (secondWord.empty())
			throw std::runtime_error{"Le mot clef object doit etre suivi d un nom d objet."};
		pos += secondWord.size();
		parsingInformations.skipSpaces();

		CppUtils::Logger::logInformation("+Object \""s + secondWord + '"', false);
		pos += secondWord.length();
		parsingInformations.skipSpaces();
		if (src.at(pos) != '{')
			throw std::runtime_error{"La declaration d un objet doit etre encadree par des accolades."};
		++pos;

		auto object = std::make_unique<Object>(secondWord, &scope);
		auto objectParsingInformations = Parser::ParsingInformations{*object, *object, src, pos};
		CppUtils::Logger::logInformation("Object "s + object->getName().data() + ':', false);

		parsingInformations.skipSpaces();
		while (parsingInformations.currentChar() != '}')
		{
			objectParsingInformations.parseInstruction();
			parsingInformations.skipSpaces();
		}
		++pos;

		return object;
	}

	std::unique_ptr<AST::Scope::Type::Value> Object::interpret()
	{
		dynamic_cast<AST::Scope::ObjectScope&>(getScope().findScope(AST::Scope::ObjectScopeType)).addInstance(this);
		return std::make_unique<AST::Scope::Type::Number>();
	}
}