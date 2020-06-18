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
		static constexpr const auto Type = "Bracket"sv;

		explicit Bracket(Scope::BaseScope* scope = nullptr):
			Core::Instruction{std::string{Type}},
			VariableScope{scope}
		{}
		virtual ~Bracket() = default;

		std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Bracket>(*this);
		}

		void indexe() override final
		{
			for (auto& instruction : m_instructions)
				instruction->indexe();
		}
		
		std::unique_ptr<Type::IValue> interpret() override final;
	};
}
