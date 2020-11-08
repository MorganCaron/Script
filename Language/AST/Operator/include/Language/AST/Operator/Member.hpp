#pragma once

#include <unordered_map>

#include <CppUtils.hpp>
#include <Language/AST/Operator/Operator.hpp>

namespace Language::AST::Operator
{
	class Member final:
		public Operator
	{
	public:
		static constexpr auto Type = CppUtils::Type::TypeId{"Member"};

		explicit Member(Scope::NormalScope* scope):
			Operator{Type, scope, eOperatorPriority::MEMBER_ACCESS}
		{}
		virtual ~Member() = default;
		
		std::unique_ptr<Type::IValue> interpret() override final
		{
			const auto& operand0 = m_instructions[0];
			const auto& operand1 = m_instructions[1];

			const auto value0 = operand0->interpret();

			auto instance = Type::ensureType<Object::Type::Instance>(value0)->getValue();
			const auto method = Core::ensureInstruction<::Language::AST::Instruction::FunctionCall>(operand1);			
			return method->execute(*instance);
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return m_instructions[1]->getReturnType();
		}
	};
}
