#pragma once

#include <Language/AST/Value/Value.hpp>
#include <Language/AST/Type/Number.hpp>

namespace Script::Language::AST::Value
{
	class Number final: public Value<Type::Number>
	{
	public:
		static constexpr auto Type = CppUtils::Type::Token{"Number"};

		explicit Number(std::unique_ptr<Type::Number>&& number):
			Value<Type::Number>{std::move(number), Type}
		{}
	};
}
