#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Object/Value.hpp>
#include <Language/AST/Object/Instantiation.hpp>

namespace Language::Parser::Value
{
	inline std::unique_ptr<AST::Core::Instruction> parseInstance(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos, verbose] = cursor;

		auto keyword = cursor.getWordAndSkipIt();
		if (keyword != "new")
			return nullptr;
		cursor.skipSpaces();

		auto className = cursor.getWordRequired("Le mot clef object doit etre suivi d un nom d objet.");
		cursor.skipSpaces();

		if (cursor.getChar() == '(')
			++pos;
		
		auto instantiation = std::make_unique<AST::Object::Instantiation>(std::move(className), &scope);
		auto instantiationParsingInformations = AST::ParsingTools::Cursor{*instantiation, *instantiation, src, pos, verbose};
		if (verbose)
			CppUtils::Log::Logger::logInformation("new "s + instantiation->getName().data() + "(", false);

		cursor.skipSpaces();
		while (cursor.getChar() != ',' && cursor.getChar() != ')')
		{
			auto value = parseValue(instantiationParsingInformations);
			if (value == nullptr)
				throw std::runtime_error{"L argument de l instantiation doit etre une valeur ou doit retourner une valeur."};
			instantiation->addInstruction(std::move(value));
			cursor.skipSpaces();
			if (cursor.getChar() == ',')
			{
				if (verbose)
					CppUtils::Log::Logger::logInformation(", ", false);
				++pos;
			}
		}
		if (cursor.getChar() == ')')
			++pos;
		if (verbose)
			CppUtils::Log::Logger::logInformation(")", false);

		return instantiation;
	}
}
