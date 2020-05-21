#pragma once

#include <Language/AST/Scope/FunctionScope.hpp>
#include <Language/AST/Scope/Object.hpp>

namespace Language::AST::Scope
{
	constexpr static const ScopeType ObjectScopeType = 3;

	class ObjectScope: public FunctionScope
	{
	public:
		ObjectScope(BaseScope* scope = nullptr, ScopeType scopeType = ObjectScopeType):
			FunctionScope{scope, scopeType}
		{}
		virtual ~ObjectScope() = default;

		inline void addInstance(Type::Object* instance)
		{
			m_instances.emplace_back(instance);
		}

	private:
		std::vector<Type::Object*> m_instances;
	};
}
