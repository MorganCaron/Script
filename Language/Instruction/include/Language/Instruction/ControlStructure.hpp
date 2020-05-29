#pragma once

#include <CppUtils.hpp>
#include <Language/Parser/Parser.hpp>
#include <Language/AST/Scope/BaseScope.hpp>

namespace Language::Instruction
{
	// if then while else do switch case repeat break for
	enum class eControlStructureSort
	{
		IF,
		WHILE
	};

	class ControlStructure final:
		public CppUtils::Type::Named,
		public AST::Instruction,
		public AST::Scope::NormalScope,
		public AST::InstructionContainer
	{
	public:
		static constexpr const auto Type = "Control structure"sv;

		explicit ControlStructure(std::string name, AST::Scope::BaseScope* scope);
		virtual ~ControlStructure() = default;

		std::unique_ptr<AST::Instruction> cloneInstruction() const override
		{
			return std::make_unique<ControlStructure>(*this);
		}

		static std::unique_ptr<AST::Instruction> parse(Parser::ParsingInformations& parsingInformations);
		std::unique_ptr<AST::Scope::Type::Value> interpret() override final;

	private:
		eControlStructureSort m_sort;
	};
}
