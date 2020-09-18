#pragma once

#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Namespace/NamespaceScope.hpp>

namespace Language::AST::Namespace
{
	class NamespaceCall final:
		public CppUtils::Type::Named,
		public Core::Instruction,
		public Scope::NormalScope,
		public Core::InstructionContainer
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Namespace Call"};
		static constexpr const auto Separator = "::"sv;

		explicit NamespaceCall(std::string name, Scope::BaseScope* scope = nullptr):
			CppUtils::Type::Named{std::move(name)},
			Core::Instruction{Type},
			Scope::NormalScope{scope}
		{}

		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override final
		{
			return std::make_unique<NamespaceCall>(*this);
		}

		std::unique_ptr<AST::Type::IValue> interpret() override final
		{
			return m_instructions[0]->interpret();
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return m_instructions[0]->getReturnType();
		}
	};
}
