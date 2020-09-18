#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Operator/Member.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Operator
{
	inline std::unique_ptr<AST::Core::Instruction> parseMember(AST::ParsingTools::Cursor& cursor, std::unique_ptr<AST::Core::Instruction>&& lhs)
	{
		auto& [container, scope, src, pos, verbose] = cursor;

		if (cursor.getChar() != '.')
			return nullptr;
		
		auto member = std::make_unique<AST::Operator::Member>(&scope);
		auto memberParsingInformations = AST::ParsingTools::Cursor{*member, *member, src, ++pos, verbose};
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
