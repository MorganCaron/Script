#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Instruction/FunctionCall.hpp>

namespace Language::Parser::Value
{
	inline std::unique_ptr<AST::Core::Instruction> parseFunctionCall(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;
		
		auto functionName = cursor.getKeyword();
		if (functionName.empty())
			return nullptr;
		cursor.pos += functionName.length();
		context.skipSpacesAndComments();

		if (cursor.getChar() != '(')
			return nullptr;
		++cursor.pos;

		auto functionCall = std::make_unique<AST::Instruction::FunctionCall>(std::move(functionName), &scope);
		auto functionCallParsingInformations = AST::ParsingTools::Context{*functionCall, *functionCall, cursor, verbose};
		if (verbose)
			CppUtils::Log::Logger::logInformation(functionCall->getName().data() + "("s, false);

		context.skipSpacesAndComments();
		while (cursor.getChar() != ',' && cursor.getChar() != ')')
		{
			auto value = parseOperation(functionCallParsingInformations);
			if (value == nullptr)
				throw std::runtime_error{"L argument de la fonction doit etre une valeur ou doit retourner une valeur."};
			functionCall->addArgument(std::move(value));
			context.skipSpacesAndComments();
			if (cursor.getChar() == ',')
			{
				if (verbose)
					CppUtils::Log::Logger::logInformation(", ", false);
				++cursor.pos;
			}
			else if (cursor.getChar() != ')')
				throw std::runtime_error{"Une virgule ou une fermeture de parenthese est requise apres un argument de fonction."};
		}
		if (cursor.getChar() == ')')
			++cursor.pos;
		if (verbose)
			CppUtils::Log::Logger::logInformation(")", false);

		return functionCall;
	}
}
