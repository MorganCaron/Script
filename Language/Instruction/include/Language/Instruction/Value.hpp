#pragma once

#include <Language/Parser/Parser.hpp>
#include <Language/AST/Scope/Type/Number.hpp>
#include <Language/AST/Scope/Type/String.hpp>
#include <Language/AST/Scope/BaseScope.hpp>

namespace Language::Instruction
{
	class Value final:
		public AST::Instruction,
		public AST::Scope::NormalScope
	{
	public:
		static constexpr const auto Type = "Value"sv;

		explicit Value(std::unique_ptr<AST::Scope::Type::Value>&& value, AST::Scope::BaseScope* scope):
			AST::Instruction{std::string{Type}},
			AST::Scope::NormalScope{scope},
			m_value{std::move(value)}
		{}
		Value(const Value& src);
		Value(Value&&) noexcept = default;
		virtual ~Value() = default;
		Value& operator=(const Value& rhs);
		Value& operator=(Value&&) noexcept= default;

		void setValue(std::unique_ptr<AST::Scope::Type::Value>&& value);
		std::unique_ptr<AST::Scope::Type::Value> getValue() const;

		std::unique_ptr<AST::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Value>(*this);
		}
		
		static std::unique_ptr<Value> parse(Parser::ParsingInformations& parsingInformations);

		std::unique_ptr<AST::Scope::Type::Value> interpret() override final;

	private:
		std::unique_ptr<AST::Scope::Type::Value> m_value;
	};
}
