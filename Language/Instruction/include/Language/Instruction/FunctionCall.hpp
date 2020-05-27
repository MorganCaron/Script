#pragma once

#include <CppUtils.hpp>
#include <Language/Parser/Parser.hpp>
#include <Language/AST/Scope/BaseScope.hpp>
#include <Language/AST/Scope/Object.hpp>

namespace Language::Instruction
{
	class FunctionCall final:
		public CppUtils::Type::Named,
		public AST::Instruction,
		public AST::Scope::NormalScope,
		public AST::InstructionContainer
	{
	public:
		static constexpr const auto type = "Function call"sv;

		explicit FunctionCall(std::string name, AST::Scope::BaseScope* scope):
			CppUtils::Type::Named{std::move(name)},
			AST::Instruction{std::string{type}},
			AST::Scope::NormalScope{scope}
		{}
		virtual ~FunctionCall() = default;

		std::unique_ptr<AST::Instruction> cloneInstruction() const override
		{
			return std::make_unique<FunctionCall>(*this);
		}

		static std::unique_ptr<Instruction> parse(Parser::ParsingInformations& parsingInformations);
		std::unique_ptr<AST::Scope::Type::Value> interpret() override final;

		std::unique_ptr<AST::Scope::Type::Value> execute(AST::Scope::Type::Object* object) const;
	};
}
