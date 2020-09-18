#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/BaseScope.hpp>
#include <Language/AST/Object/Instance.hpp>

namespace Language::AST::Object
{
	class Instantiation final:
		public CppUtils::Type::Named,
		public Core::Instruction,
		public Scope::NormalScope,
		public Core::InstructionContainer
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Instantiation"};

		explicit Instantiation(std::string name, Scope::BaseScope* scope):
			CppUtils::Type::Named{std::move(name)},
			Core::Instruction{Type},
			Scope::NormalScope{scope}
		{}
		virtual ~Instantiation() = default;

		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Instantiation>(*this);
		}
		
		std::unique_ptr<AST::Type::IValue> interpret() override final;

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			static const auto type = CppUtils::Type::TypeId{getName()};
			return type;
		}
	};
}
