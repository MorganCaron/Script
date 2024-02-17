#include <Language/AST/Object/Class.hpp>

#include <Language/AST/Object/ObjectScope.hpp>

namespace Script::Language::AST::Object
{
	void Class::indexe()
	{
		auto& objectScope = dynamic_cast<ObjectScope&>(getParentScope().findScope(ObjectScopeType));
		objectScope.addClass(getName(), std::make_unique<Type::Instance>(std::make_shared<Instance>(getName().data(), *this)));
	}
}
