#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Instruction/ControlStructure.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseControlStructure(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos] = cursor;

		auto keyword = cursor.getWord();
		static const auto controlStructureWords = std::vector<std::string>{"if", "then", "while", "else", "do", "switch", "case", "repeat", "break", "for"};
		if (std::find(controlStructureWords.begin(), controlStructureWords.end(), keyword) == controlStructureWords.end())
			return nullptr;
		pos += keyword.length();
		cursor.skipSpaces();

		auto controlStructure = std::make_unique<AST::Instruction::ControlStructure>(keyword, &scope);
		auto controlStructureParsingInformations = AST::ParsingTools::Cursor{*controlStructure, *controlStructure, src, pos};

		CppUtils::Logger::logInformation(controlStructure->getName().data() + " ("s, false);
		controlStructure->addInstruction(Value::parseValue(controlStructureParsingInformations));
		CppUtils::Logger::logInformation(") ", false);

		cursor.skipSpaces();
		if (cursor.getChar() == ':')
			++pos;
		
		if (parseInstruction(controlStructureParsingInformations) == nullptr)
			throw std::runtime_error{"La condition doit etre suivie d une instruction."};
		
		return controlStructure;
	}
}
