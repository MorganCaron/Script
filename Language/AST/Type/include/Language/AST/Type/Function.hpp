#pragma once

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Type
{
	constexpr char FunctionTypename[] = "Function";
	using Function = Type<FunctionTypename, std::function>;
}
