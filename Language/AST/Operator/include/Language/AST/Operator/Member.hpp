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

		Member(Scope::BaseScope* scope):
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

			CppUtils::Log::Logger::logDebug(operand0->getInstructionType().name);
			CppUtils::Log::Logger::logDebug(operand1->getInstructionType().name);
			/*
			if (operand0->getInstructionType() != Variable::Variable::Type)
				throw std::runtime_error{"L operande a gauche de l operateur = doit etre une variable."};
			*/
			/*
			const auto value0 = operand0->interpret();
			const auto value1 = operand1->interpret();
			const auto number0 = Type::ensureType<Type::Number>(value0)->getValue();
			const auto number1 = Type::ensureType<Type::Number>(value1)->getValue();
			*/

			/*
			if (value0->getType() != Object::Instance::type)
				throw std::runtime_error{"L element avant le point doit etre un objet."};
			auto object = dynamic_cast<Object::Instance*>(value0.get());
			if (object == nullptr)
				throw std::runtime_error{"Cet objet ne peut pas etre utilise ici car il a ete supprime."};
			if (operand1->getInstructionType() != FunctionCall::type)
				throw std::runtime_error{"L element apres le point d un objet doit etre une fonction membre."};
			result = dynamic_cast<FunctionCall*>(operand1.get())->execute(object);
			*/

			return std::make_unique<Type::Number>(0);
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return m_instructions[1]->getReturnType();
		}
	};
}
