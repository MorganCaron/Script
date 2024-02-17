#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Instruction/ControlStructure.hpp>
#include <Language/Parser/Value/OperationParser.hpp>

namespace Script::Language::Parser::Instruction
{
	std::unique_ptr<AST::Core::Instruction> parseControlStructure(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		auto keyword = std::string{cursor.getKeyword()};
		static const auto controlStructureWords = std::vector<std::string>{"if", "then", "while", "else", "do", "switch", "case", "repeat", "break", "for"};
		if (std::find(controlStructureWords.begin(), controlStructureWords.end(), keyword) == controlStructureWords.end())
			return nullptr;
		cursor.pos += keyword.length();
		context.skipSpacesAndComments();

		auto controlStructure = std::make_unique<AST::Instruction::ControlStructure>(keyword, &scope);
		auto controlStructureParsingInformations = AST::ParsingTools::Context{*controlStructure, *controlStructure, cursor, verbose};

		if (verbose)
			CppUtils::Log::Logger::logInformation(controlStructure->getName().data() + " ("s, false);
		controlStructure->addInstruction(Value::parseOperation(controlStructureParsingInformations));
		if (verbose)
			CppUtils::Log::Logger::logInformation(") ", false);

		context.skipSpacesAndComments();
		if (cursor.getChar() == ':')
			++cursor.pos;
		
		auto firstBlock = parseInstruction(controlStructureParsingInformations);
		if (!firstBlock)
			throw std::runtime_error{"La condition doit etre suivie d une instruction."};
		controlStructure->addInstruction(std::move(firstBlock));

		return controlStructure;
	}
}
