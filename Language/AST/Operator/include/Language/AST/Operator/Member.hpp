#pragma once

#include <unordered_map>

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/BaseScope.hpp>

namespace Language::AST::Operator
{
	class Member final:
		public Core::Instruction,
		public Scope::NormalScope,
		public Core::InstructionContainer
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Member"};

		explicit Member(Scope::BaseScope* scope):
			Core::Instruction{Type},
			Scope::NormalScope{scope}
		{}
		virtual ~Member() = default;

		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Member>(*this);
		}
		
		std::unique_ptr<Type::IValue> interpret() override final
		{
			const auto& operand0 = m_instructions[0];
			const auto& operand1 = m_instructions[1];

			// CppUtils::Log::Logger::logDebug(operand0->getInstructionType().name);
			// CppUtils::Log::Logger::logDebug(operand1->getInstructionType().name);

			const auto value0 = operand0->interpret();
			
			auto& instance = Type::ensureType<Object::Type::Instance>(value0)->getValue();
			
			if (operand1->getInstructionType() != ::Language::AST::Instruction::FunctionCall::Type)
				throw std::runtime_error{"L element apres le point d un objet doit etre une fonction membre."};
			
			auto method = dynamic_cast<::Language::AST::Instruction::FunctionCall&>(*operand1);			
			return method.execute(instance);
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return m_instructions[1]->getReturnType();
		}
	};
}
