#pragma once

#include <unordered_map>

#include <CppUtils.hpp>
#include <Language/Parser/Parser.hpp>
#include <Language/AST/Scope/BaseScope.hpp>

namespace Language::Instruction
{
	enum class eOperatorPriority
	{
		ASSIGNMENT,
		BINARY,
		ADDSUB,
		MULDIV,
		MEMFUNC
	};

	class Operator final:
		public CppUtils::Type::Named,
		public AST::Instruction,
		public AST::Scope::NormalScope,
		public AST::InstructionContainer
	{
	public:
		Operator(std::string name, AST::Scope::BaseScope* scope);
		virtual ~Operator() = default;

		inline eOperatorPriority getPriority() const
		{
			return m_priority;
		}

		std::unique_ptr<AST::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Operator>(*this);
		}

		static std::unique_ptr<AST::Instruction> parseOperand(Parser::ParsingInformations& parsingInformations);
		static std::unique_ptr<Operator> parseOperator(Parser::ParsingInformations& parsingInformations);
		static std::unique_ptr<AST::Instruction> parseOperation(Parser::ParsingInformations& parsingInformations, std::unique_ptr<AST::Instruction>&& lhs = nullptr, std::unique_ptr<Operator>&& nextOperator = nullptr);
		std::unique_ptr<AST::Scope::Type::Value> interpret() override final;

	private:
		std::unique_ptr<AST::Scope::Type::Value> doOp(const std::unique_ptr<AST::Scope::Type::Value>& val1, std::string_view op, const std::unique_ptr<AST::Scope::Type::Value>& val2);
		
		eOperatorPriority m_priority;
	};

	std::ostream& operator<<(std::ostream& os, const Operator& op);
}
