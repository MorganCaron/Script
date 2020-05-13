#pragma once

#include <CppUtils.hpp>
#include <Language/Scope/BaseScope.hpp>
#include <Language/Scope/Object.hpp>

#include "Instruction.hpp"
#include "InstructionContainer.hpp"

namespace Language
{
	class FunctionCall:
		public CppUtils::Type::Named,
		public Instruction,
		public Scope::NormalScope,
		public InstructionContainer
	{
	public:
		FunctionCall(std::string name, Scope::BaseScope* scope):
			CppUtils::Type::Named{std::move(name)},
			Instruction{InstructionType::FUNCTIONCALL},
			NormalScope{scope}
		{}
		virtual ~FunctionCall() = default;

		std::unique_ptr<Instruction> cloneInstruction() const override
		{
			return std::make_unique<FunctionCall>(*this);
		}

		void parse(ParsingInformations& parsingInformations) override final;
		std::unique_ptr<Scope::Type::Value> interpret() override final;

		std::unique_ptr<Scope::Type::Value> execute(Scope::Type::Object* object) const;

		static std::unique_ptr<Instruction> parse(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations, std::string word);
	};
}
