#pragma once

#include <cstddef>

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Type
{
	constexpr const char VoidTypename[] = "Void";
	using Void = Type<VoidTypename, std::nullptr_t>;
}
