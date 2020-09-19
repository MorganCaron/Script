#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Instruction/Return.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Instruction
{
	inline std::unique_ptr<AST::Core::Instruction> parseReturn(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt(AST::Instruction::Return::Keyword))
			return nullptr;
		context.skipSpacesAndComments();

		if (verbose)
			CppUtils::Log::Logger::logInformation(AST::Instruction::Return::Keyword.data() + " "s, false);

		context.skipSpacesAndComments();
		auto returnStatement = std::make_unique<AST::Instruction::Return>(&scope);
		auto value = Value::parseValue(context);
		if (value == nullptr)
			throw std::runtime_error{"Le mot clef return doit etre suivi d une valeur."};
		context.parseSemicolon();
		returnStatement->addInstruction(std::move(value));
		return returnStatement;
	}
}
