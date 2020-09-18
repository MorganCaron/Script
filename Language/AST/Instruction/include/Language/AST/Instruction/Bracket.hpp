#pragma once

#include <memory>

#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Variable/VariableScope.hpp>

namespace Language::AST::Instruction
{
	class Bracket final:
		public Core::Instruction,
		public Variable::VariableScope,
		public Core::InstructionContainer
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Bracket"};

		explicit Bracket(Scope::BaseScope* scope = nullptr):
			Core::Instruction{Type},
			VariableScope{scope},
			m_returnType{Type::VoidType}
		{}
		virtual ~Bracket() = default;

		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Bracket>(*this);
		}

		void indexe() override final
		{
			for (auto& instruction : m_instructions)
				instruction->indexe();
		}
		
		std::unique_ptr<Type::IValue> interpret() override final;

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return m_returnType;
		}

	private:
		CppUtils::Type::TypeId m_returnType;
	};
}
