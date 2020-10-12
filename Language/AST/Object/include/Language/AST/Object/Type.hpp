#pragma once

#include <Language/AST/Type/Type.hpp>
#include <Language/AST/Object/Instance.hpp>

namespace Language::AST::Object::Type
{
	constexpr const char InstanceTypename[] = "Instance";
	using Instance = AST::Type::Type<InstanceTypename, Instance>;
}
