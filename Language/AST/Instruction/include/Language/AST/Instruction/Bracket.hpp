#pragma once

#include <memory>

#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Variable/VariableScope.hpp>
#include <Language/AST/Type/Void.hpp>

namespace Language::AST::Instruction
{
	class Bracket final:
		public Core::InstructionContainer,
		public Variable::VariableScope
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Bracket"};

		explicit Bracket(Scope::NormalScope* scope = nullptr):
			Core::InstructionContainer{Type},
			VariableScope{scope},
			m_returnType{Type::Void::TypeId}
		{}
		virtual ~Bracket() = default;

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
