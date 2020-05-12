#pragma once

#include "FunctionScope.hpp"
#include "Object.hpp"

namespace Language::Scope
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
