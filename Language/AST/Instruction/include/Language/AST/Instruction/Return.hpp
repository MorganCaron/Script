#pragma once

#include <memory>

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>

namespace Language::AST::Instruction
{
	class Return final:
		public Core::Instruction,
		public Core::InstructionContainer,
		public Scope::NormalScope
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Return"};
		static constexpr const auto Keyword = "return"sv;

		explicit Return(Scope::BaseScope* scope):
			Core::Instruction{Type},
			Scope::NormalScope{scope}
		{}

		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Return>(*this);
		}
		
		std::unique_ptr<Type::IValue> interpret() override final
		{
			return m_instructions.at(0)->interpret();
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return m_instructions.at(0)->getReturnType();
		}
	};
}
