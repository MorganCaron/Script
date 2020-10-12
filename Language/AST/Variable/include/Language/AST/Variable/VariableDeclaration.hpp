#pragma once

#include <string>

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Variable/VariableScope.hpp>

namespace Language::AST::Variable
{
	class VariableDeclaration final:
		public CppUtils::Type::Named,
		public Core::InstructionContainer,
		public Scope::NormalScope
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Variable declaration"};

		explicit VariableDeclaration(Scope::NormalScope* scope, VariableSignature variableSignature):
			CppUtils::Type::Named{variableSignature.name},
			Core::InstructionContainer{Type},
			Scope::NormalScope{scope}
		{
			declare(std::move(variableSignature));
		}

		[[nodiscard]] bool exists() const;
	private:
		void declare(VariableSignature variableSignature);
	public:
		void setValue(std::unique_ptr<Type::IValue>&& value);
		[[nodiscard]] const std::unique_ptr<Type::IValue>& getValue() const;
		
		void indexe() override final;
		std::unique_ptr<Type::IValue> interpret() override final;
		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final;
	};

	std::ostream& operator<<(std::ostream& os, const VariableDeclaration& variable);
}
