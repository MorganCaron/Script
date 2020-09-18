#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Instruction/FunctionCall.hpp>

namespace Language::Parser::Value
{
	inline std::unique_ptr<AST::Core::Instruction> parseFunctionCall(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos, verbose] = cursor;
		
		auto functionName = cursor.getWord();
		if (functionName.empty())
			return nullptr;
		pos += functionName.length();
		cursor.skipSpaces();

		if (cursor.getChar() != '(')
			return nullptr;
		++pos;

		auto functionCall = std::make_unique<AST::Instruction::FunctionCall>(std::move(functionName), &scope);
		auto functionCallParsingInformations = AST::ParsingTools::Cursor{*functionCall, *functionCall, src, pos, verbose};
		if (verbose)
			CppUtils::Log::Logger::logInformation(functionCall->getName().data() + "("s, false);

		cursor.skipSpaces();
		while (cursor.getChar() != ',' && cursor.getChar() != ')')
		{
			auto value = parseValue(functionCallParsingInformations);
			if (value == nullptr)
				throw std::runtime_error{"L argument de la fonction doit etre une valeur ou doit retourner une valeur."};
			functionCall->addArgument(std::move(value));
			cursor.skipSpaces();
			if (cursor.getChar() == ',')
			{
				if (verbose)
					CppUtils::Log::Logger::logInformation(", ", false);
				++pos;
			}
			else if (cursor.getChar() != ')')
				throw std::runtime_error{"Une virgule ou une fermeture de parenthese est requise apres un argument de fonction."};
		}
		if (cursor.getChar() == ')')
			++pos;
		if (verbose)
			CppUtils::Log::Logger::logInformation(")", false);

		return functionCall;
	}
}
