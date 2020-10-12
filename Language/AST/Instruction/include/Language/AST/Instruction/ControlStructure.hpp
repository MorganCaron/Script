#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/NormalScope.hpp>
#include <Language/AST/Type/Void.hpp>

namespace Language::AST::Instruction
{
	// A implémenter: if then while else do switch case repeat break for
	enum class eControlStructureSort
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
		static constexpr const auto Type = CppUtils::Type::TypeId{"Control structure"};

		explicit ControlStructure(std::string name, Scope::NormalScope* scope);
		virtual ~ControlStructure() = default;

		std::unique_ptr<Type::IValue> interpret() override final;

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return Type::Void::TypeId;
		}

	private:
		eControlStructureSort m_sort;
	};
}
