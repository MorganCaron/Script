#pragma once

#include <Language/AST/Value/Value.hpp>
#include <Language/AST/Object/Type.hpp>

namespace Language::AST::Object::Value
{
	class Instance final: public Value<Type::Instance>
	{
	public:
		static constexpr const auto Typename = "Instance"sv;

		explicit Instance(std::unique_ptr<Type::Instance>&& string):
			Value<Type::Instance>{string, Typename}
		{}

		std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Instance>(*this);
		}
	};
}
