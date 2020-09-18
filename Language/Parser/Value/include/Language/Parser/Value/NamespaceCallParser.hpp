#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Namespace/NamespaceCall.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Language::Parser::Value
{
	inline std::unique_ptr<AST::Core::Instruction> parseNamespaceCall(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos, verbose] = cursor;

		auto name = cursor.getWordAndSkipIt();
		if (!cursor.isKeywordSkipIt(AST::Namespace::NamespaceCall::Separator))
			return nullptr;

		auto namespaceCall = std::make_unique<AST::Namespace::NamespaceCall>(name, &scope);
		auto namespaceCallParsingInformations = AST::ParsingTools::Cursor{*namespaceCall, *namespaceCall, src, pos, verbose};

		if (verbose)
			CppUtils::Log::Logger::logInformation(std::string{namespaceCall->getName()} + AST::Namespace::NamespaceCall::Separator.data(), false);
		auto value = parseValue(namespaceCallParsingInformations);
		if (value == nullptr)
			throw std::runtime_error{"Le namespace doit etre suivi par une valeur, une fonction ou une classe."};
		namespaceCall->addInstruction(std::move(value));
		return namespaceCall;
	}
}
