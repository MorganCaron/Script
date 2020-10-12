#pragma once

#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Namespace/NamespaceScope.hpp>
#include <Language/AST/Type/Void.hpp>

namespace Language::AST::Namespace
{
	class NamespaceDeclaration final:
		public CppUtils::Type::Named,
		public Core::InstructionContainer,
		public Scope::NormalScope
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Namespace Declaration"};
		static constexpr const auto Keyword = "namespace"sv;

		explicit NamespaceDeclaration(std::string name, Scope::NormalScope* scope):
			CppUtils::Type::Named{std::move(name)},
			Core::InstructionContainer{Type},
			Scope::NormalScope{scope}
		{}
		
		void indexe() override final
		{
			CppUtils::Log::Logger::logDetail("Declare "s + Keyword.data() + " " + getName().data());
			auto& namespaceScope = getParentScope().findScope<class NamespaceScope>();
			namespaceScope.addNamespace(CppUtils::Type::TypeId{getName()}, std::make_unique<NamespaceScope>(&getParentScope()));
		}

		std::unique_ptr<AST::Type::IValue> interpret() override final
		{
			return std::make_unique<AST::Type::Void>(nullptr);
		}
		
		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return AST::Type::Void::TypeId;
		}
	};
}
