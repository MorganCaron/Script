#pragma once
/*
#include <unordered_map>

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/BaseScope.hpp>

namespace Language::AST::Instruction
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
		public Core::Instruction,
		public Scope::NormalScope,
		public Core::InstructionContainer
	{
	public:
		static constexpr const auto Type = "Operator"sv;

		Operator(std::string name, Scope::BaseScope* scope);
		virtual ~Operator() = default;

		inline eOperatorPriority getPriority() const
		{
			return m_priority;
		}

		std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Operator>(*this);
		}
		
		std::unique_ptr<Type::IValue> interpret() override final;

	private:
		std::unique_ptr<Type::IValue> doOp(const std::unique_ptr<Type::IValue>& val1, std::string_view op, const std::unique_ptr<Type::IValue>& val2);
		
		eOperatorPriority m_priority;
	};

	std::ostream& operator<<(std::ostream& os, const Operator& op);
}
*/
