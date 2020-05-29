#pragma once

#include <CppUtils.hpp>
#include <Language/Parser/Parser.hpp>
#include <Language/AST/Scope/VariableScope.hpp>
#include <Language/AST/Scope/Type/Function.hpp>

namespace Language::Instruction
{
	class FunctionDeclaration final:
		public CppUtils::Type::Named,
		public AST::Instruction,
		public AST::Scope::VariableScope,
		public AST::InstructionContainer,
		public AST::Scope::Type::ITFunction<std::unique_ptr<AST::Scope::Type::Value>(const AST::Scope::Type::Args&)>
	{
	public:
		static constexpr const auto Type = "Function declaration"sv;
		static constexpr const auto Keyword = "function"sv;
		
		explicit FunctionDeclaration(std::string name, AST::Scope::BaseScope* scope);
		virtual ~FunctionDeclaration() = default;
		
		std::unique_ptr<AST::Scope::Type::ITFunction<std::unique_ptr<AST::Scope::Type::Value>(const AST::Scope::Type::Args&)>> cloneFunction() const override;

		std::unique_ptr<AST::Instruction> cloneInstruction() const override
		{
			return std::make_unique<FunctionDeclaration>(*this);
		}

		void addArgument(std::string name, AST::Scope::VariableScope::VariableSignature&& signature);

		std::unique_ptr<AST::Scope::Type::Value> operator()(const AST::Scope::Type::Args& arguments) override final;

		static std::unique_ptr<AST::Instruction> parse(Parser::ParsingInformations& parsingInformations);
		std::unique_ptr<AST::Scope::Type::Value> interpret() override final;
		
	private:
		std::vector<std::string> m_arguments;
	};

	std::ostream& operator<<(std::ostream& os, const FunctionDeclaration& functionDeclaration);
}
