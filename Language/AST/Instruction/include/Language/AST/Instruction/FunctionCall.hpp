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
		static constexpr const auto type = "Function call"sv;

		explicit FunctionCall(std::string name, Scope::BaseScope* scope):
			CppUtils::Type::Named{std::move(name)},
			Core::Instruction{std::string{type}},
			Scope::NormalScope{scope}
		{}
		virtual ~FunctionCall() = default;

		std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<FunctionCall>(*this);
		}
		
		std::unique_ptr<Type::IValue> interpret() override final;

		std::unique_ptr<Type::IValue> execute(Object::Instance* object) const;
	};
}
