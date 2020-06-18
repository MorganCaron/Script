#pragma once

#include <Language/AST/ParsingTools/Cursor.hpp>
#include <Language/AST/Variable/Variable.hpp>

namespace Language::Parser::Value
{
	inline std::unique_ptr<AST::Core::Instruction> parseVariable(AST::ParsingTools::Cursor& cursor)
	{
		auto& [container, scope, src, pos] = cursor;

		auto variableName = cursor.getWordAndSkipIt();
		if (variableName.empty())
			return nullptr;
		const auto& variableScope = dynamic_cast<const AST::Variable::VariableScope&>(scope.findScope(AST::Variable::VariableScopeType));
		if (!variableScope.variableSignatureExists(variableName))
			return nullptr;
		
		CppUtils::Logger::logInformation(variableName, false);
		return std::make_unique<AST::Variable::Variable>(std::move(variableName), &scope);
	}
}
