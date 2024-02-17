#pragma once

#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Namespace/NamespaceScope.hpp>

namespace Script::Language::AST::Namespace
{
	class NamespaceCall final:
		public CppUtils::Type::Named,
		public Core::InstructionContainer,
		public Scope::NormalScope
	{
	public:
		static constexpr auto Type = CppUtils::Type::Token{"Namespace Call"};
		static constexpr auto Separator = "::"sv;

		explicit NamespaceCall(std::string name, Scope::NormalScope* scope = nullptr):
			CppUtils::Type::Named{std::move(name)},
			Core::InstructionContainer{Type},
			Scope::NormalScope{scope},
			m_namespaceId{getName()}
		{}

		[[nodiscard]] Scope::NormalScope& findScope(const Scope::ScopeType scopeType) override
		{
			auto& namespaceScope = getParentScope().findScope<NamespaceScope>();
			auto& targetedNamespace = namespaceScope.getNamespace(m_namespaceId);
			return targetedNamespace.findScope(scopeType);
		}

		[[nodiscard]] const Scope::NormalScope& findScope(const Scope::ScopeType scopeType) const override
		{
			const auto& namespaceScope = getParentScope().findScope<NamespaceScope>();
			const auto& targetedNamespace = namespaceScope.getNamespace(m_namespaceId);
			return targetedNamespace.findScope(scopeType);
		}

		std::unique_ptr<AST::Type::IValue> interpret() override final
		{
			return m_instructions[0]->interpret();
		}
 
		[[nodiscard]] const CppUtils::Type::Token& getReturnType() const override final
		{
			return m_instructions[0]->getReturnType();
		}

	private:
		CppUtils::Type::Token m_namespaceId;
	};
}
