#pragma once

#include <CppUtils.hpp>
#include <Language/Scope/VariableScope.hpp>
#include <Language/Scope/Type/Function.hpp>

#include "Instruction.hpp"
#include "InstructionContainer.hpp"

namespace Language
{
	class FunctionStatement:
		public CppUtils::Type::Named,
		public Instruction,
		public Scope::VariableScope,
		public InstructionContainer,
		public Scope::Type::ITFunction<std::unique_ptr<Scope::Type::Value>(const Scope::Type::Args&)>
	{
	public:
		FunctionStatement(std::string name, Scope::BaseScope* scope);
		virtual ~FunctionStatement() = default;
		
		std::unique_ptr<Scope::Type::ITFunction<std::unique_ptr<Scope::Type::Value>(const Scope::Type::Args&)>> cloneFunction() const override;

		std::unique_ptr<Instruction> cloneInstruction() const override
		{
			return std::make_unique<FunctionStatement>(*this);
		}

		void parse(ParsingInformations& parsingInformations) override final;
		std::unique_ptr<Scope::Type::Value> interpret() override final;

		std::unique_ptr<Scope::Type::Value> operator()(const Scope::Type::Args& arguments) override final;

		static void parse(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations);

	private:
		std::vector<std::string> m_args;
	};

	std::ostream& operator<<(std::ostream& os, const FunctionStatement& functionStatement);
}
