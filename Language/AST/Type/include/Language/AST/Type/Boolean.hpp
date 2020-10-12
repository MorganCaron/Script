#pragma once

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Type
{
	constexpr const char BooleanTypename[] = "Boolean";
	using Boolean = Type<BooleanTypename, bool>;
}
