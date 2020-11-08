#pragma once

#include <Language/AST/Type/Void.hpp>
#include <Language/AST/Namespace/NamespaceScope.hpp>

namespace Language::AST::Namespace
{
	class ImportDeclaration final:
		public Core::Instruction,
		public Scope::NormalScope
	{
	public:
		static constexpr auto Type = CppUtils::Type::TypeId{"Import declaration"};
		static constexpr auto Keyword = "import"sv;
		
		explicit ImportDeclaration(Scope::NormalScope* scope):
			Core::Instruction{Type},
			Scope::NormalScope{scope}
		{}
		
		std::unique_ptr<Type::IValue> interpret() override final
		{
			return std::make_unique<Type::Void>(nullptr);
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return Type::Void::TypeId;
		}
	};
}
