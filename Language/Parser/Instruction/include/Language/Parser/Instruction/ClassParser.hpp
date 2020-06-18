#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Object/Class.hpp>
#include <Language/Parser/Instruction/InstructionParser.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseClass(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos] = cursor;

		if (!cursor.isKeywordSkipIt(AST::Object::Class::Keyword))
			return nullptr;
		cursor.skipSpaces();

		auto className = cursor.getWordRequired("Le mot clef object doit etre suivi d un nom d objet.");
		cursor.skipSpaces();

		CppUtils::Logger::logInformation(AST::Object::Class::Keyword.data() + " "s + className);
		auto object = std::make_unique<AST::Object::Class>(className, &scope);
		auto objectParsingInformations = AST::ParsingTools::Cursor{*object, *object, src, pos};
		auto instruction = parseInstruction(objectParsingInformations);
		if (!instruction)
			throw std::runtime_error{"Une instruction est requise dans la declaration de la classe."};
		object->addInstruction(std::move(instruction));
		return object;
	}
}
