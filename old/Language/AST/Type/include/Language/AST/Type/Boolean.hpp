#pragma once

#include <Language/AST/Type/Type.hpp>

namespace Script::Language::AST::Type
{
	constexpr char BooleanTypename[] = "Boolean";
	using Boolean = Type<BooleanTypename, bool>;
}
