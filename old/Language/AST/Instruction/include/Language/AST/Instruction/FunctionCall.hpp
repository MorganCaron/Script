#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/NormalScope.hpp>
#include <Language/AST/Object/Instance.hpp>

namespace Script::Language::AST::Instruction
{
	class FunctionCall final:
		public CppUtils::Type::Named,
		public Core::InstructionContainer,
		public Scope::NormalScope
	{
	public:
		static constexpr auto Type = CppUtils::Type::Token{"Function call"};

		explicit FunctionCall(std::string name, Scope::NormalScope* scope):
			CppUtils::Type::Named{std::move(name)},
			Core::InstructionContainer{Type},
			Scope::NormalScope{scope}
		{}

		void addArgument(std::unique_ptr<Core::Instruction>&& argument)
		{
			m_argumentTypes.emplace_back(argument->getReturnType());
			addInstruction(std::move(argument));
		}
		
		std::unique_ptr<Type::IValue> interpret() override final;
		[[nodiscard]] const CppUtils::Type::Token& getReturnType() const override final;

		std::unique_ptr<Type::IValue> execute(Object::Instance& instance) const;
	
	private:
		std::vector<CppUtils::Type::Token> m_argumentTypes;
	};
}
