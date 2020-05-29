#pragma once

#include <Language/Parser/Parser.hpp>
#include <Language/AST/Scope/Object.hpp>
#include <Language/AST/Scope/Type/Number.hpp>

namespace Language::Instruction
{
	class Object final:
		public AST::Scope::Type::Object,
		public AST::Instruction,
		public AST::InstructionContainer
	{
	public:
		static constexpr const auto Type = "Object"sv;
		static constexpr const auto Keyword = "class"sv;

		explicit Object(std::string name, AST::Scope::BaseScope* scope = nullptr):
			AST::Scope::Type::Object{std::move(name), scope},
			AST::Instruction{std::string{Type}}
		{}
		Object(const Object& src);
		Object(Object&&) = default;
		virtual ~Object() = default;
		Object &operator=(const Object& rhs);
		Object &operator=(Object&&) = default;

		std::unique_ptr<AST::Scope::Type::Value> cloneValue() const override
		{
			return std::make_unique<AST::Scope::Type::Object>(*this);
		}

		std::unique_ptr<AST::Instruction> cloneInstruction() const override
		{
			return std::make_unique<Object>(*this);
		}

		static std::unique_ptr<AST::Instruction> parse(Parser::ParsingInformations& parsingInformations);
		std::unique_ptr<AST::Scope::Type::Value> interpret() override final;
	};
}
