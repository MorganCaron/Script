#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/BaseScope.hpp>
#include <Language/AST/Object/Instance.hpp>

namespace Language::AST::Instruction
{
	class FunctionCall final:
		public CppUtils::Type::Named,
		public Core::Instruction,
		public Scope::NormalScope,
		public Core::InstructionContainer
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Function call"};

		explicit FunctionCall(std::string name, Scope::BaseScope* scope):
			CppUtils::Type::Named{std::move(name)},
			Core::Instruction{Type},
			Scope::NormalScope{scope}
		{}
		virtual ~FunctionCall() = default;

		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<FunctionCall>(*this);
		}

		void addArgument(std::unique_ptr<Core::Instruction>&& argument)
		{
			m_argumentTypes.emplace_back(argument->getReturnType());
			addInstruction(std::move(argument));
		}
		
		std::unique_ptr<Type::IValue> interpret() override final;
		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final;

		std::unique_ptr<Type::IValue> execute(Object::Instance& object) const;
	
	private:
		std::vector<CppUtils::Type::TypeId> m_argumentTypes;
	};
}
