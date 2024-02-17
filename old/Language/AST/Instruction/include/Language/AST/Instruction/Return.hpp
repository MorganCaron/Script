#pragma once

#include <memory>

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>

namespace Script::Language::AST::Instruction
{
	using namespace std::literals;
	
	class Return final:
		public Core::InstructionContainer,
		public Scope::NormalScope
	{
	public:
		static constexpr auto Type = CppUtils::Type::Token{"Return"};
		static constexpr auto Keyword = "return"sv;

		explicit Return(Scope::NormalScope* scope):
			Core::InstructionContainer{Type},
			Scope::NormalScope{scope}
		{}
		
		std::unique_ptr<Type::IValue> interpret() override final
		{
			return m_instructions[0]->interpret();
		}

		[[nodiscard]] const CppUtils::Type::Token& getReturnType() const override final
		{
			return m_instructions[0]->getReturnType();
		}
	};
}
