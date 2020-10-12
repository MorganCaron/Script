#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/NormalScope.hpp>

namespace Language::AST::Operator
{
	enum class eOperatorPriority
	{
		ASSIGNMENT,
		COMPARISON,
		LOGICAL,
		ARITHMETIC_LOW,
		ARITHMETIC_MEDIUM,
		ARITHMETIC_HIGH,
		MEMBER_ACCESS
	};

	class Operator:
		public Core::InstructionContainer,
		public Scope::NormalScope
	{
	public:
		explicit Operator(CppUtils::Type::TypeId instructionType, Scope::NormalScope* scope, eOperatorPriority priority):
			Core::InstructionContainer{std::move(instructionType)},
			Scope::NormalScope{scope},
			m_priority{priority}
		{}
		virtual ~Operator() = default;

		[[nodiscard]] inline const eOperatorPriority& getPriority() const noexcept
		{
			return m_priority;
		}

	private:
		eOperatorPriority m_priority;
	};
}
