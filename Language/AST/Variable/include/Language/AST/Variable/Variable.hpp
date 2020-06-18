#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/Instruction.hpp>
#include <Language/AST/Scope/BaseScope.hpp>

namespace Language::AST::Variable
{
	class Variable final:
		public CppUtils::Type::Named,
		public Core::Instruction,
		public Scope::NormalScope
	{
	public:
		static constexpr const auto Type = "Variable"sv;

		explicit Variable(std::string name, Scope::BaseScope* scope):
			CppUtils::Type::Named{std::move(name)},
			Core::Instruction{std::string{Type}},
			Scope::NormalScope{scope}
		{}
		Variable(const Variable&) = default;
		Variable(Variable&&) = default;
		virtual ~Variable()
		{}
		Variable& operator=(const Variable&) = default;
		Variable& operator=(Variable&&) = default;

		bool exists() const;
		void setValue(std::unique_ptr<Type::IValue>&& value);
		const std::unique_ptr<Type::IValue>& getValue() const;

		std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Variable>(*this);
		}
		
		std::unique_ptr<Type::IValue> interpret() override final;
	};

	std::ostream& operator<<(std::ostream& os, const Variable& variable);
}
