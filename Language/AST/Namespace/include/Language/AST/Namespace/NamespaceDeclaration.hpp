#pragma once

#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Namespace/NamespaceScope.hpp>

namespace Language::AST::Namespace
{
	class NamespaceDeclaration final:
		public CppUtils::Type::Named,
		public Core::Instruction,
		public Core::InstructionContainer,
		public Scope::NormalScope
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Namespace Declaration"};
		static constexpr const auto Keyword = "namespace"sv;

		explicit NamespaceDeclaration(std::string name, Scope::BaseScope* scope):
			CppUtils::Type::Named{std::move(name)},
			Core::Instruction{Type},
			Scope::NormalScope{scope}
		{}

		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override final
		{
			return std::make_unique<NamespaceDeclaration>(*this);
		}
		
		void indexe() override final
		{
			auto& namespaceScope = dynamic_cast<class NamespaceScope&>(getScope().findScope(NamespaceScopeType));
			namespaceScope.addNamespace(CppUtils::Type::TypeId{getName()}, std::make_unique<NamespaceScope>(&getScope()));
			m_instructions[0]->indexe();
		}

		std::unique_ptr<AST::Type::IValue> interpret() override final
		{
			return std::make_unique<AST::Type::Number>(0);
		}
		
		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return AST::Type::VoidType;
		}
	};
}
