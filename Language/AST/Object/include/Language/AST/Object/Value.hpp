#pragma once

#include <Language/AST/Value/Value.hpp>
#include <Language/AST/Object/Type.hpp>

namespace Language::AST::Object::Value
{
	class Instance final: public AST::Value::Value<Type::Instance>
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Instance"};

		explicit Instance(std::unique_ptr<Type::Instance>&& instance):
			AST::Value::Value<Type::Instance>{std::move(instance), Type}
		{}

		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Instance>(*this);
		}
	};
}
