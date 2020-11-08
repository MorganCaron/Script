#pragma once

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Type
{
	constexpr char StringTypename[] = "String";
	using String = Type<StringTypename, std::string>;
}
