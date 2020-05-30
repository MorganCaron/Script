#include <Language/Instruction/Class.hpp>

#include <Language/AST/Scope/ObjectScope.hpp>
#include <Language/Instruction/FunctionDeclaration.hpp>

namespace Language::Instruction
{
	Class::Class(Class const &src):
		AST::Scope::Type::Object{src},
		AST::Instruction{src},
		AST::InstructionContainer{src}
	{
		for (const std::pair<const std::string, std::unique_ptr<AST::Scope::FunctionType>>& pair : getFunctions())
			addFunction(pair.first, std::make_unique<FunctionDeclaration>(static_cast<const FunctionDeclaration&>(*pair.second)));
	}

	Class &Class::operator=(Class const &rhs)
	{
		AST::Scope::Type::Object::operator=(rhs);
		AST::Instruction::operator=(rhs);
		AST::InstructionContainer::operator=(rhs);
		for (const std::pair<const std::string, std::unique_ptr<AST::Scope::FunctionType>>& pair : getFunctions())
			addFunction(pair.first, std::make_unique<FunctionDeclaration>(static_cast<const FunctionDeclaration&>(*pair.second)));
		return *this;
	}

	std::unique_ptr<AST::Instruction> Class::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		auto keyword = parsingInformations.nextWord();
		if (keyword != Keyword)
			return std::unique_ptr<Instruction>{nullptr};
		pos += Keyword.length();
		parsingInformations.skipSpaces();

		auto className = parsingInformations.nextWord();
		if (className.empty())
			throw std::runtime_error{"Le mot clef object doit etre suivi d un nom d objet."};
		pos += className.size();
		parsingInformations.skipSpaces();

		CppUtils::Logger::logInformation(Keyword.data() + " "s + className);
		auto object = std::make_unique<Class>(className, &scope);
		auto objectParsingInformations = Parser::ParsingInformations{*object, *object, src, pos};
		auto instruction = Parser::parseInstruction(objectParsingInformations);
		if (!instruction)
			throw std::runtime_error{"Une instruction est requise dans la declaration de la classe."};
		object->addInstruction(std::move(instruction));
		return object;
	}

	std::unique_ptr<AST::Scope::Type::Value> Class::interpret()
	{
		CppUtils::Logger::logInformation("Declare "s + Keyword.data() + " " + getName().data() + "{", false);
		auto& objectScope = dynamic_cast<AST::Scope::ObjectScope&>(getScope().findScope(AST::Scope::ObjectScopeType));
		objectScope.addInstance(this);
		CppUtils::Logger::logInformation("}");
		return std::make_unique<AST::Scope::Type::Number>();
	}
}
