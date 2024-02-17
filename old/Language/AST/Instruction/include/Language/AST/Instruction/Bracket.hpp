#pragma once

#include <memory>

#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Variable/VariableScope.hpp>
#include <Language/AST/Type/Void.hpp>

namespace Script::Language::AST::Instruction
{
	class Bracket final:
		public Core::InstructionContainer,
		public Variable::VariableScope
	{
	public:
		static constexpr auto Type = CppUtils::Type::Token{"Bracket"};

		explicit Bracket(Scope::NormalScope* scope = nullptr):
			Core::InstructionContainer{Type},
			VariableScope{scope},
			m_returnType{Type::Void::Token}
		{}
		virtual ~Bracket() = default;

		void indexe() override final
		{
			for (auto& instruction : m_instructions)
				instruction->indexe();
		}
		
		std::unique_ptr<Type::IValue> interpret() override final;

		[[nodiscard]] const CppUtils::Type::Token& getReturnType() const override final
		{
			return m_returnType;
		}

	private:
		CppUtils::Type::Token m_returnType;
	};
}
