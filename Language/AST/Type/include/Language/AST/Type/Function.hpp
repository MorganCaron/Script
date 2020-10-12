#pragma once

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Type
{
	constexpr const char FunctionTypename[] = "Function";
	using Function = Type<FunctionTypename, std::function>;
}
