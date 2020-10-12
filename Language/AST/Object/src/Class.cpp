#include <Language/AST/Object/Class.hpp>

#include <Language/AST/Object/ObjectScope.hpp>

namespace Language::AST::Object
{
	void Class::indexe()
	{
		CppUtils::Log::Logger::logDetail("Declare "s + Keyword.data() + " " + getName().data());
		auto& objectScope = dynamic_cast<ObjectScope&>(getParentScope().findScope(ObjectScopeType));
		objectScope.addClass(getName(), std::make_unique<Type::Instance>(Instance{getName().data(), *this}));
		m_instructions[0]->indexe();
	}
}
