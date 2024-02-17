#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/NormalScope.hpp>
#include <Language/AST/Type/Void.hpp>

namespace Script::Language::AST::Instruction
{
	// A implémenter: if then while else do switch case repeat break for
	enum class eControlStructureSort: char
	{
		IF,
		WHILE
	};

	class ControlStructure final:
		public CppUtils::Type::Named,
		public Core::InstructionContainer,
		public Scope::NormalScope
	{
	public:
		static constexpr auto Type = CppUtils::Type::Token{"Control structure"};

		explicit ControlStructure(std::string name, Scope::NormalScope* scope);
		virtual ~ControlStructure() = default;

		std::unique_ptr<Type::IValue> interpret() override final;

		[[nodiscard]] const CppUtils::Type::Token& getReturnType() const override final
		{
			return Type::Void::Token;
		}

	private:
		eControlStructureSort m_sort;
	};
}
