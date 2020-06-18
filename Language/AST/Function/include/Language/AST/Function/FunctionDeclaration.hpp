#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Variable/VariableScope.hpp>
#include <Language/AST/Type/Function.hpp>

namespace Language::AST::Function
{
	class FunctionDeclaration final:
		public CppUtils::Type::Named,
		public Core::Instruction,
		public Variable::VariableScope,
		public Core::InstructionContainer,
		public Type::ITFunction<std::unique_ptr<Type::IValue>(const Type::Args&)>
	{
	public:
		static constexpr const auto Type = "Function declaration"sv;
		static constexpr const auto Keyword = "function"sv;
		
		explicit FunctionDeclaration(std::string name, Scope::BaseScope* scope);
		virtual ~FunctionDeclaration() = default;
		
		std::unique_ptr<Type::ITFunction<std::unique_ptr<Type::IValue>(const Type::Args&)>> cloneFunction() const override;

		std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<FunctionDeclaration>(*this);
		}

		void addArgument(std::string name, Variable::VariableScope::VariableSignature&& signature);

		std::unique_ptr<Type::IValue> operator()(const Type::Args& arguments) override final;
		
		void indexe() override final;
		std::unique_ptr<Type::IValue> interpret() override final;
		
	private:
		std::vector<std::string> m_argumentNames;
	};

	std::ostream& operator<<(std::ostream& os, const FunctionDeclaration& functionDeclaration);
}
