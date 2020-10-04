#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Operator/NotEquality.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Core::Instruction> parseNotEquality(AST::ParsingTools::Context& context, std::unique_ptr<AST::Core::Instruction>&& lhs)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (!cursor.isEqualSkipIt("!="))
			return nullptr;
		
		auto notEquality = std::make_unique<AST::Operator::NotEquality>(&scope);
		auto notEqualityParsingInformations = AST::ParsingTools::Context{*notEquality, *notEquality, cursor, verbose};
		notEquality->addInstruction(std::move(lhs));
		if (verbose)
			CppUtils::Log::Logger::logInformation(" != ", false);
		auto value = Value::parseValue(notEqualityParsingInformations);
		if (value == nullptr)
			throw std::runtime_error{"L operateur != doit etre suivi d une valeur."};
		notEquality->addInstruction(std::move(value));
		return notEquality;
	}
}
