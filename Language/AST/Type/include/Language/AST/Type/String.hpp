#pragma once

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Type
{
	struct StringTag { 
		static constexpr const auto Name = "String"sv; 
	};

	using String = Type<StringTag, std::string>;
}
