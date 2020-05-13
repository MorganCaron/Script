#pragma once

#include <Language/Scope/Type/Number.hpp>
#include <Language/Scope/Type/String.hpp>
#include <Language/Scope/BaseScope.hpp>

#include "Instruction.hpp"
#include "InstructionContainer.hpp"

namespace Language
{
	class Value:
		public Instruction,
		public Scope::NormalScope
	{
	public:
		Value(std::unique_ptr<Scope::Type::Value>&& value, Scope::BaseScope* scope):
			Instruction{InstructionType::VALUE},
			NormalScope{scope},
			m_value{std::move(value)}
		{}
		Value(const Value& src);
		Value(Value&&) noexcept = default;
		virtual ~Value() = default;
		Value& operator=(const Value& rhs);
		Value& operator=(Value&&) noexcept= default;

		void setValue(std::unique_ptr<Scope::Type::Value>&& value);
		std::unique_ptr<Scope::Type::Value> getValue() const;

		std::unique_ptr<Instruction> cloneInstruction() const override
		{
			return std::make_unique<Value>(*this);
		}

		void parse(ParsingInformations& parsingInformations) override final
		{
			static_cast<void>(parsingInformations);
		}
		std::unique_ptr<Scope::Type::Value> interpret() override final;

		static std::unique_ptr<Value> parse(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations);
		static std::unique_ptr<Scope::Type::Number> parseNumber(InstructionContainer& container, ParsingInformations& parsingInformations);
		static std::unique_ptr<Scope::Type::String> parseString(InstructionContainer& container, ParsingInformations& parsingInformations);

	private:
		std::unique_ptr<Scope::Type::Value> m_value;
	};
}
