#pragma once

#include <Language/Scope/Object.hpp>
#include <Language/Scope/Type/Number.hpp>

#include "Instruction.hpp"
#include "InstructionContainer.hpp"

namespace Language
{
	class Object:
		public Scope::Type::Object,
		public Instruction,
		public InstructionContainer
	{
	public:
		Object(std::string name, Scope::BaseScope* scope = nullptr):
			Scope::Type::Object{std::move(name), scope},
			Instruction{InstructionType::OBJECT}
		{}
		Object(const Object& src);
		Object(Object&&) = default;
		virtual ~Object() = default;
		Object &operator=(const Object& rhs);
		Object &operator=(Object&&) = default;

		std::unique_ptr<Scope::Type::Value> cloneValue() const override
		{
			return std::make_unique<Scope::Type::Object>(*this);
		}

		std::unique_ptr<Instruction> cloneInstruction() const override
		{
			return std::make_unique<Object>(*this);
		}

		void parse(ParsingInformations& parsingInformations) override final;
		std::unique_ptr<Scope::Type::Value> interpret() override final;

		static void parse(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations);
	};
}
