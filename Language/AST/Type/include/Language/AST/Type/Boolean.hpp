#pragma once

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Type
{
	struct BooleanTag { 
		static constexpr const auto Name = "Boolean"sv; 
	};

	using Boolean = Type<BooleanTag, bool>;
}
