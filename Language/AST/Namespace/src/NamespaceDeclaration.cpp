#include <Language/AST/Namespace/NamespaceDeclaration.hpp>

namespace Language::AST::Namespace
{
	void NamespaceDeclaration::indexe()
	{
		CppUtils::Log::Logger::logInformation("Declare "s + Keyword.data() + " " + getName().data() + "{", false);
		auto& NamespaceScope = dynamic_cast<class NamespaceScope&>(getScope().findScope(NamespaceScopeType));
		NamespaceScope.addNamespace(getName(), std::make_unique<NamespaceDeclaration>(*this));
		CppUtils::Log::Logger::logInformation("}");
		m_instructions[0]->indexe();
	}
}
