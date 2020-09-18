#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Instruction/Return.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseReturn(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos, verbose] = cursor;

		if (!cursor.isKeywordSkipIt(AST::Instruction::Return::Keyword))
			return nullptr;
		cursor.skipSpaces();

		if (verbose)
			CppUtils::Log::Logger::logInformation(AST::Instruction::Return::Keyword.data() + " "s, false);

		cursor.skipSpaces();
		auto returnStatement = std::make_unique<AST::Instruction::Return>(&scope);
		auto value = Value::parseValue(cursor);
		if (value == nullptr)
			throw std::runtime_error{"Le mot clef return doit etre suivi d une valeur."};
		cursor.parseSemicolon();
		returnStatement->addInstruction(std::move(value));
		return returnStatement;
	}
}
