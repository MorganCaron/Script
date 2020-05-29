#pragma once

#include <CppUtils.hpp>
#include <Language/Parser/Parser.hpp>
#include <Language/AST/Scope/BaseScope.hpp>

namespace Language::Instruction
{
	class VariableDeclaration final:
		public CppUtils::Type::Named,
		public AST::Instruction,
		public AST::Scope::NormalScope
	{
	public:
		static constexpr const auto Type = "Variable declaration"sv;

		explicit VariableDeclaration(std::string name, AST::Scope::BaseScope* scope, std::unique_ptr<AST::Scope::Type::Value>&& value, bool constant):
			CppUtils::Type::Named{std::move(name)},
			AST::Instruction{std::string{Type}},
			AST::Scope::NormalScope{scope}
		{
			declare(std::move(value), constant);
		}
		VariableDeclaration(const VariableDeclaration&) = default;
		VariableDeclaration(VariableDeclaration&&) = default;
		virtual ~VariableDeclaration()
		{}
		VariableDeclaration& operator=(const VariableDeclaration&) = default;
		VariableDeclaration& operator=(VariableDeclaration&&) = default;

		bool exists() const;
	private:
		void declare(std::unique_ptr<AST::Scope::Type::Value>&& value, bool constant);
	public:
		void setValue(std::unique_ptr<AST::Scope::Type::Value>&& value);
		const std::unique_ptr<AST::Scope::Type::Value>& getValue() const;

		std::unique_ptr<AST::Instruction> cloneInstruction() const override
		{
			return std::make_unique<VariableDeclaration>(*this);
		}

		static std::unique_ptr<AST::Instruction> parse(Parser::ParsingInformations& parsingInformations);
		std::unique_ptr<AST::Scope::Type::Value> interpret() override final;
	};

	std::ostream& operator<<(std::ostream& os, const VariableDeclaration& variable);
}
