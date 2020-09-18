#pragma once

#include <string>

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Variable/VariableScope.hpp>

namespace Language::AST::Variable
{
	class VariableDeclaration final:
		public CppUtils::Type::Named,
		public Core::Instruction,
		public Core::InstructionContainer,
		public Scope::NormalScope
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Variable declaration"};

		explicit VariableDeclaration(Scope::BaseScope* scope, VariableSignature variableSignature):
			CppUtils::Type::Named{variableSignature.name},
			Core::Instruction{Type},
			Scope::NormalScope{scope}
		{
			declare(std::move(variableSignature));
		}
		VariableDeclaration(const VariableDeclaration&) = default;
		VariableDeclaration(VariableDeclaration&&) = default;
		virtual ~VariableDeclaration()
		{}
		VariableDeclaration& operator=(const VariableDeclaration&) = default;
		VariableDeclaration& operator=(VariableDeclaration&&) = default;

		[[nodiscard]] bool exists() const;
	private:
		void declare(VariableSignature variableSignature);
	public:
		void setValue(std::unique_ptr<Type::IValue>&& value);
		[[nodiscard]] const std::unique_ptr<Type::IValue>& getValue() const;

		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<VariableDeclaration>(*this);
		}
		
		std::unique_ptr<Type::IValue> interpret() override final;
		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final;
	};

	std::ostream& operator<<(std::ostream& os, const VariableDeclaration& variable);
}
