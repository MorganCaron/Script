#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Variable/Variable.hpp>

namespace Language::Parser::Value
{
	inline std::unique_ptr<AST::Core::Instruction> parseVariable(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		auto variableName = cursor.getKeywordAndSkipIt();
		if (variableName.empty())
			return nullptr;
		const auto& variableScope = dynamic_cast<const AST::Variable::VariableScope&>(scope.findScope(AST::Variable::VariableScopeType));
		if (!variableScope.variableSignatureExists(variableName))
			return nullptr;
		
		if (verbose)
			CppUtils::Log::Logger::logInformation(variableName, false);
		return std::make_unique<AST::Variable::Variable>(std::move(variableName), &scope);
	}
}
