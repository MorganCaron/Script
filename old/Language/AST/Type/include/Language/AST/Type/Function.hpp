#pragma once

#include <Language/AST/Type/Type.hpp>

namespace Script::Language::AST::Type
{
	constexpr char FunctionTypename[] = "Function";
	using Function = Type<FunctionTypename, std::function>;
}
