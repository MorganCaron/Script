#pragma once

#include <Language/AST/Function/FunctionScope.hpp>
#include <Language/AST/Object/Instance.hpp>

namespace Language::AST::Object
{
	constexpr static const Scope::ScopeType ObjectScopeType = 3;

	class ObjectScope: public Function::FunctionScope
	{
	public:
		ObjectScope(BaseScope* scope = nullptr, Scope::ScopeType scopeType = ObjectScopeType):
			FunctionScope{scope, scopeType}
		{}
		virtual ~ObjectScope() = default;

		inline void addInstance(Instance* instance)
		{
			m_instances.emplace_back(instance);
		}

	private:
		std::vector<Instance*> m_instances;
	};
}
