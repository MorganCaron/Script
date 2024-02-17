#pragma once

#include <Language/AST/Value/Value.hpp>
#include <Language/AST/Type/String.hpp>

namespace Script::Language::AST::Value
{
	class String final: public Value<Type::String>
	{
	public:
		static constexpr auto Type = CppUtils::Type::Token{"String"};

		explicit String(std::unique_ptr<Type::String>&& string):
			Value<Type::String>{std::move(string), Type}
		{}
	};
}
