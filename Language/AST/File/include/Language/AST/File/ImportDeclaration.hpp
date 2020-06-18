#pragma once

#include <Language/AST/Type/Number.hpp>
#include <Language/AST/File/FileScope.hpp>

namespace Language::AST::File
{
	class ImportDeclaration final:
		public Core::Instruction,
		public Scope::NormalScope
	{
	public:
		static constexpr const auto Type = "Import declaration"sv;
		static constexpr const auto Keyword = "import"sv;
		
		explicit ImportDeclaration(Scope::BaseScope* scope):
			Core::Instruction{std::string{Type}},
			Scope::NormalScope{scope}
		{}
		
		std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<ImportDeclaration>(*this);
		}
		
		std::unique_ptr<Type::IValue> interpret() override final
		{
			return std::make_unique<Type::Number>(0);
		}
	};
}
