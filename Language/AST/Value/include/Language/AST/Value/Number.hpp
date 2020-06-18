#pragma once

#include <Language/AST/Value/Value.hpp>
#include <Language/AST/Type/Number.hpp>

namespace Language::AST::Value
{
	class Number final: public Value<Type::Number>
	{
	public:
		static constexpr const auto Typename = "Number"sv;

		explicit Number(std::unique_ptr<Type::Number>&& number):
			Value<Type::Number>{std::move(number), std::string{Typename}}
		{}

		std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Number>(*this);
		}
	};
}
