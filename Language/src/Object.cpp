#include "Language/Object.hpp"

#include "Language/AST.hpp"
#include "Language/FunctionStatement.hpp"

namespace Language
{
	Object::Object(Object const &src):
		Scope::Type::Object{src},
		Instruction{src},
		InstructionContainer{src}
	{
		for (const std::pair<const std::string, std::unique_ptr<Scope::FunctionType>>& pair : getFunctions())
			addFunction(pair.first, std::make_unique<FunctionStatement>(static_cast<const FunctionStatement&>(*pair.second)));
	}

	Object &Object::operator=(Object const &rhs)
	{
		Scope::Type::Object::operator=(rhs);
		Instruction::operator=(rhs);
		InstructionContainer::operator=(rhs);
		for (const std::pair<const std::string, std::unique_ptr<Scope::FunctionType>>& pair : getFunctions())
			addFunction(pair.first, std::make_unique<FunctionStatement>(static_cast<const FunctionStatement&>(*pair.second)));
		return *this;
	}

	void Object::parse(ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;

		CppUtils::Logger::logInformation("Object "s + getName().data() + ':', false);
		AST::parseSpace(parsingInformations);
		while (parsingInformations.currentChar() != '}')
		{
			AST::parseInstruction(*this, *this, parsingInformations);
			AST::parseSpace(parsingInformations);
		}
		++pos;
	}

	std::unique_ptr<Scope::Type::Value> Object::interpret()
	{
		dynamic_cast<Scope::ObjectScope&>(getScope().findScope(Scope::ObjectScopeType)).addInstance(this);
		return std::make_unique<Scope::Type::Number>();
	}

	void Object::parse(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;
		auto word = parsingInformations.nextWord();

		if (word.empty())
			throw std::runtime_error{"Le mot clef object doit etre suivi d un nom d objet."};
		CppUtils::Logger::logInformation("+Object \""s + word + '"', false);
		pos += word.length();
		AST::parseSpace(parsingInformations);
		if (code.at(pos) != '{')
			throw std::runtime_error{"La declaration d un objet doit etre encadree par des accolades."};
		auto object = std::make_unique<Object>(word, &scope);
		++pos;
		object->parse(parsingInformations);
		container.addInstruction(std::move(object));
	}
}
