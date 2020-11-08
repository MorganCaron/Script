#pragma once

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Type
{
	constexpr char BooleanTypename[] = "Boolean";
	using Boolean = Type<BooleanTypename, bool>;
}
