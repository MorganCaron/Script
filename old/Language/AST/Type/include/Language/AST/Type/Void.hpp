#pragma once

#include <cstddef>

#include <Language/AST/Type/Type.hpp>

namespace Script::Language::AST::Type
{
	constexpr char VoidTypename[] = "Void";
	using Void = Type<VoidTypename, std::nullptr_t>;
}
