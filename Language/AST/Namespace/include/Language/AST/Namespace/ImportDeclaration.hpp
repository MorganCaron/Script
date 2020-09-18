#pragma once

#include <Language/AST/Type/Number.hpp>
#include <Language/AST/Namespace/NamespaceScope.hpp>

namespace Language::AST::Namespace
{
	class ImportDeclaration final:
		public Core::Instruction,
		public Scope::NormalScope
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Import declaration"};
		static constexpr const auto Keyword = "import"sv;
		
		explicit ImportDeclaration(Scope::BaseScope* scope):
			Core::Instruction{Type},
			Scope::NormalScope{scope}
		{}
		
		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<ImportDeclaration>(*this);
		}
		
		std::unique_ptr<Type::IValue> interpret() override final
		{
			return std::make_unique<Type::Number>(0);
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return Type::VoidType;
		}
	};
}
