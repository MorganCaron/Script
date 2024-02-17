#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Namespace/NamespaceCall.hpp>
#include <Language/AST/Instruction/FunctionCall.hpp>
#include <Language/AST/Variable/Variable.hpp>
#include <Language/Parser/Value/ValueParser.hpp>

namespace Script::Language::Parser::Value
{
	std::unique_ptr<AST::Core::Instruction> parseNamespaceCall(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		auto name = std::string{cursor.getKeywordAndSkipIt()};
		if (!cursor.isEqualSkipIt(AST::Namespace::NamespaceCall::Separator))
			return nullptr;
		
		auto namespaceCall = std::make_unique<AST::Namespace::NamespaceCall>(std::move(name), &scope);
		if (verbose)
			CppUtils::Log::Logger::logInformation(std::string{namespaceCall->getName()} + AST::Namespace::NamespaceCall::Separator.data(), false);
		
		auto namespaceCallParsingInformations = AST::ParsingTools::Context{*namespaceCall, *namespaceCall, cursor, verbose};
		auto value = parseValue(namespaceCallParsingInformations);

		if (value == nullptr || !(value->isType(AST::Namespace::NamespaceCall::Type) || value->isType(AST::Instruction::FunctionCall::Type) || value->isType(AST::Variable::Variable::Type)))
			throw std::runtime_error{"Le namespace doit etre suivi par un namespace, une fonction ou une variable."};
		
		namespaceCall->addInstruction(std::move(value));
		return namespaceCall;
	}
}
