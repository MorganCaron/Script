#pragma once

#include <Language/AST/Value/Value.hpp>
#include <Language/AST/Type/String.hpp>

namespace Language::AST::Value
{
	class String final: public Value<Type::String>
	{
	public:
		static constexpr const auto Typename = "String"sv;

		explicit String(std::unique_ptr<Type::String>&& string):
			Value<Type::String>{std::move(string), std::string{Typename}}
		{}

		std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<String>(*this);
		}
	};
}