#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/BaseScope.hpp>

namespace Language::AST::Instruction
{
	// if then while else do switch case repeat break for
	enum class eControlStructureSort
	{
		IF,
		WHILE
	};

	class ControlStructure final:
		public CppUtils::Type::Named,
		public Core::Instruction,
		public Scope::NormalScope,
		public Core::InstructionContainer
	{
	public:
		static constexpr const auto Type = "Control structure"sv;

		explicit ControlStructure(std::string name, Scope::BaseScope* scope);
		virtual ~ControlStructure() = default;

		std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<ControlStructure>(*this);
		}

		std::unique_ptr<Type::IValue> interpret() override final;

	private:
		eControlStructureSort m_sort;
	};
}