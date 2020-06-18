#pragma once

#include <string>

#include <CppUtils.hpp>
#include <Language/AST/Core/Instruction.hpp>
#include <Language/AST/Scope/BaseScope.hpp>

namespace Language::AST::Variable
{
	class VariableDeclaration final:
		public CppUtils::Type::Named,
		public Core::Instruction,
		public Scope::NormalScope
	{
	public:
		static constexpr const auto Type = "Variable declaration"sv;

		explicit VariableDeclaration(std::string name, Scope::BaseScope* scope, bool constant, std::unique_ptr<Type::IValue>&& value, std::string type):
			CppUtils::Type::Named{std::move(name)},
			Core::Instruction{std::string{Type}},
			Scope::NormalScope{scope}
		{
			declare(constant, std::move(value), std::move(type));
		}
		VariableDeclaration(const VariableDeclaration&) = default;
		VariableDeclaration(VariableDeclaration&&) = default;
		virtual ~VariableDeclaration()
		{}
		VariableDeclaration& operator=(const VariableDeclaration&) = default;
		VariableDeclaration& operator=(VariableDeclaration&&) = default;

		bool exists() const;
	private:
		void declare(bool constant, std::unique_ptr<Type::IValue>&& value, std::string type);
	public:
		void setValue(std::unique_ptr<Type::IValue>&& value);
		const std::unique_ptr<Type::IValue>& getValue() const;

		std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<VariableDeclaration>(*this);
		}
		
		std::unique_ptr<Type::IValue> interpret() override final;
	};

	std::ostream& operator<<(std::ostream& os, const VariableDeclaration& variable);
}
