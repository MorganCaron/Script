#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/Instruction.hpp>
#include <Language/AST/Scope/NormalScope.hpp>

namespace Language::AST::Variable
{
	class Variable final:
		public CppUtils::Type::Named,
		public Core::Instruction,
		public Scope::NormalScope
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Variable"};

		explicit Variable(std::string name, Scope::NormalScope* scope):
			CppUtils::Type::Named{std::move(name)},
			Core::Instruction{Type},
			Scope::NormalScope{scope}
		{}

		[[nodiscard]] bool exists() const;
		void setValue(std::unique_ptr<Type::IValue>&& value);
		[[nodiscard]] const std::unique_ptr<Type::IValue>& getValue() const;
		
		std::unique_ptr<Type::IValue> interpret() override final;
		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final;
	};

	std::ostream& operator<<(std::ostream& os, const Variable& variable);
}
