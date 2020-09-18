#pragma once

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Type
{
	struct FunctionTag { 
		static constexpr const auto Name = "Function"sv; 
	};

	using Function = Type<FunctionTag, std::function>;
}
