#pragma once

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Type
{
	constexpr const char StringTypename[] = "String";
	using String = Type<StringTypename, std::string>;
}
