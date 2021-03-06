#pragma once

#include <memory>

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>

namespace Language::AST::Instruction
{
	class Return final:
		public Core::InstructionContainer,
		public Scope::NormalScope
	{
	public:
		static constexpr auto Type = CppUtils::Type::TypeId{"Return"};
		static constexpr auto Keyword = "return"sv;

		explicit Return(Scope::NormalScope* scope):
			Core::InstructionContainer{Type},
			Scope::NormalScope{scope}
		{}
		
		std::unique_ptr<Type::IValue> interpret() override final
		{
			return m_instructions[0]->interpret();
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return m_instructions[0]->getReturnType();
		}
	};
}
