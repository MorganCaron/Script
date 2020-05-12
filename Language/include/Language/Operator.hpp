#pragma once

#include <CppUtils.hpp>
#include <Language/Scope/BaseScope.hpp>

#include "Instruction.hpp"
#include "InstructionContainer.hpp"

namespace Language
{
	enum class eOperatorPriority
	{
		ASSIGNMENT,
		BINARY,
		ADDSUB,
		MULDIV,
		MEMFUNC
	};

	class Operator:
		public CppUtils::Type::Named,
		public Instruction,
		public Scope::NormalScope,
		public InstructionContainer
	{
	public:
		Operator(std::string name, Language::Scope::BaseScope* scope);
		virtual ~Operator() = default;

		inline eOperatorPriority getPriority() const
		{
			return m_priority;
		}

		std::unique_ptr<Instruction> cloneInstruction() const override
		{
			return std::make_unique<Operator>(*this);
		}

		void parse([[maybe_unused]] ParsingInformations& parsingInformations) override final
		{}
		std::unique_ptr<Scope::Type::Value> interpret() override final;

	private:
		std::unique_ptr<Scope::Type::Value> doOp(const std::unique_ptr<Scope::Type::Value>& val1, std::string_view op, const std::unique_ptr<Scope::Type::Value>& val2);

	public:
		static std::unique_ptr<Instruction> parseOperand(InstructionContainer& container, Language::Scope::BaseScope& scope, ParsingInformations& parsingInformations);
		static std::unique_ptr<Operator> parseOperator(InstructionContainer& container, Language::Scope::BaseScope& scope, ParsingInformations& parsingInformations);
		static std::unique_ptr<Instruction> parseOperation(InstructionContainer& container, Language::Scope::BaseScope& scope, ParsingInformations& parsingInformations, std::unique_ptr<Instruction>&& lhs = nullptr, std::unique_ptr<Operator>&& nextOperator = nullptr);

	private:
		eOperatorPriority m_priority;
	};

	std::ostream& operator<<(std::ostream& os, const Operator& op);
}
