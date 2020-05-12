#pragma once

#include <CppUtils.hpp>
#include <Language/Scope/BaseScope.hpp>

#include "Instruction.hpp"
#include "InstructionContainer.hpp"

namespace Language
{
	enum class eControlStructureSort
	{
		IF,
		WHILE
	};

	class ControlStructure:
		public CppUtils::Type::Named,
		public Instruction,
		public Scope::NormalScope,
		public InstructionContainer
	{
	public:
		ControlStructure(std::string name, Language::Scope::BaseScope* scope);
		virtual ~ControlStructure() = default;

		std::unique_ptr<Instruction> cloneInstruction() const override
		{
			return std::make_unique<ControlStructure>(*this);
		}

		void parse(ParsingInformations& parsingInformations) override final;
		std::unique_ptr<Scope::Type::Value> interpret() override final;

	private:
		eControlStructureSort m_sort;
	};
}
