#pragma once

#include <CppUtils.hpp>
#include <Language/Scope/BaseScope.hpp>

#include "Instruction.hpp"
#include "InstructionContainer.hpp"

namespace Language
{
	class Variable:
		public CppUtils::Type::Named,
		public Instruction,
		public Scope::NormalScope
	{
	public:
		Variable(std::string name, Scope::BaseScope* scope, bool local = false):
			CppUtils::Type::Named{std::move(name)},
			Instruction{eInstructionType::VARIABLE},
			NormalScope{scope},
			m_local(local)
		{}
		Variable(const Variable& src) = default;
		Variable(Variable&& src) = default;
		virtual ~Variable()
		{}
		Variable& operator=(const Variable& rhs) = default;
		Variable& operator=(Variable&& rhs) = default;

		bool exists() const;
		void setValue(std::unique_ptr<Scope::Type::Value>&& value);
		const std::unique_ptr<Scope::Type::Value>& getValue() const;

		std::unique_ptr<Instruction> cloneInstruction() const override
		{
			return std::make_unique<Variable>(*this);
		}

		void parse([[maybe_unused]] ParsingInformations& parsingInformations) override final
		{}
		std::unique_ptr<Scope::Type::Value> interpret() override final;

		static std::unique_ptr<Instruction> parse(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations, std::string word);

	private:
		bool m_local;
	};

	std::ostream& operator<<(std::ostream& os, const Variable& variable);
}
