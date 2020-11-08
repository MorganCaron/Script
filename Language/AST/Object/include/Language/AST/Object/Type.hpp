#pragma once

#include <Language/AST/Type/Type.hpp>
#include <Language/AST/Object/Instance.hpp>

namespace Language::AST::Object::Type
{
	constexpr char InstanceTypename[] = "Instance";
	using Instance = AST::Type::Type<InstanceTypename, std::shared_ptr<Instance>>;
}
