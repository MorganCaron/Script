#pragma once

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Type
{
	struct NumberTag { 
		static constexpr const auto Name = "Number"sv; 
	};

	using Number = Type<NumberTag, double>;
}
