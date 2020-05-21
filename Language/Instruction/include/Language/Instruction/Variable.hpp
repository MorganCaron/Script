#pragma once

#include <CppUtils.hpp>
#include <Language/Parser/Parser.hpp>
#include <Language/AST/Scope/BaseScope.hpp>

namespace Language::Instruction
{
	class Variable final:
		public CppUtils::Type::Named,
		public AST::Instruction,
		public AST::Scope::NormalScope
	{
	public:
		explicit Variable(std::string name, AST::Scope::BaseScope* scope, bool local = false):
			CppUtils::Type::Named{std::move(name)},
			AST::Instruction{AST::InstructionType::VARIABLE},
			AST::Scope::NormalScope{scope},
			m_local(local)
		{}
		Variable(const Variable&) = default;
		Variable(Variable&&) = default;
		virtual ~Variable()
		{}
		Variable& operator=(const Variable&) = default;
		Variable& operator=(Variable&&) = default;

		bool exists() const;
		void setValue(std::unique_ptr<AST::Scope::Type::Value>&& value);
		const std::unique_ptr<AST::Scope::Type::Value>& getValue() const;

		std::unique_ptr<AST::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Variable>(*this);
		}

		static std::unique_ptr<AST::Instruction> parse(Parser::ParsingInformations& parsingInformations);
		std::unique_ptr<AST::Scope::Type::Value> interpret() override final;

	private:
		bool m_local;
	};

	std::ostream& operator<<(std::ostream& os, const Variable& variable);
}
