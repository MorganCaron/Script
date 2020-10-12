#pragma once

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Type
{
	constexpr const char NumberTypename[] = "Number";
	using Number = Type<NumberTypename, double>;
}
