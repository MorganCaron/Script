#include <Language/AST/Object/Instantiation.hpp>

#include <Language/AST/Object/ObjectScope.hpp>

namespace Language::AST::Object
{
	std::unique_ptr<AST::Type::IValue> Instantiation::interpret()
	{
		auto arguments = AST::Type::Args{};

		for (const auto& argument : m_instructions)
			arguments.emplace_back(dynamic_cast<Core::Instruction&>(*argument).interpret());
		const auto& objectScope = dynamic_cast<const ObjectScope&>(getScope().findScope(ObjectScopeType));
		return objectScope.instantiate(getName(), arguments);
	}
}
