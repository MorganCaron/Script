#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Object/Instantiation.hpp>

namespace Script::Language::Parser::Value
{
	[[nodiscard]] std::unique_ptr<AST::Core::Instruction> parseInstance(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;
		
		if (!cursor.isEqualSkipIt("new"))
			return nullptr;
		context.skipSpacesAndComments();

		auto className = std::string{cursor.getKeywordRequired("Le mot clef object doit etre suivi d un nom d objet.")};
		context.skipSpacesAndComments();

		if (cursor.getChar() == '(')
			++cursor.pos;
		
		auto instantiation = std::make_unique<AST::Object::Instantiation>(std::move(className), &scope);
		auto instantiationParsingInformations = AST::ParsingTools::Context{*instantiation, *instantiation, cursor, verbose};
		if (verbose)
		{
			CppUtils::Log::Logger::logInformation("new ", false);
			CppUtils::Log::Logger::logDetail(instantiation->getName(), false);
			CppUtils::Log::Logger::logInformation("(", false);
		}
		
		context.skipSpacesAndComments();
		while (cursor.getChar() != ',' && cursor.getChar() != ')')
		{
			auto value = parseOperation(instantiationParsingInformations);
			if (value == nullptr)
				throw std::runtime_error{"L argument de l instantiation doit etre une valeur ou doit retourner une valeur."};
			instantiation->addInstruction(std::move(value));
			context.skipSpacesAndComments();
			if (cursor.getChar() == ',')
			{
				if (verbose)
					CppUtils::Log::Logger::logInformation(", ", false);
				++cursor.pos;
			}
		}
		if (cursor.getChar() == ')')
			++cursor.pos;
		if (verbose)
			CppUtils::Log::Logger::logInformation(")", false);

		return instantiation;
	}
}
