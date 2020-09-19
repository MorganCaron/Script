#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Operator/Member.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Core::Instruction> parseMember(AST::ParsingTools::Context& context, std::unique_ptr<AST::Core::Instruction>&& lhs)
	{
		auto& [container, scope, cursor, verbose] = context;

		if (cursor.getChar() != '.')
			return nullptr;
		
		auto member = std::make_unique<AST::Operator::Member>(&scope);
		++cursor.pos;
		auto memberParsingInformations = AST::ParsingTools::Context{*member, *member, cursor, verbose};
		member->addInstruction(std::move(lhs));
		if (verbose)
			CppUtils::Log::Logger::logInformation(".", false);
		auto value = Value::parseValue(memberParsingInformations);
		if (value == nullptr)
			throw std::runtime_error{"L operateur . doit etre suivi d une valeur."};
		member->addInstruction(std::move(value));
		return member;
	}
}
