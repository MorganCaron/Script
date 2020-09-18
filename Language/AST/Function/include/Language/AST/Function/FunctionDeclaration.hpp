#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Variable/VariableScope.hpp>
#include <Language/AST/Function/Function.hpp>

namespace Language::AST::Function
{
	class FunctionDeclaration final:
		public CppUtils::Type::Named,
		public Core::Instruction,
		public Variable::VariableScope,
		public Core::InstructionContainer,
		public ITFunction<std::unique_ptr<Type::IValue>(const Type::Args&)>
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Function declaration"};
		static constexpr const auto Keyword = "function"sv;
		
		explicit FunctionDeclaration(std::string name, Scope::BaseScope* scope);
		virtual ~FunctionDeclaration() = default;
		
		[[nodiscard]] std::unique_ptr<ITFunction<std::unique_ptr<Type::IValue>(const Type::Args&)>> cloneFunction() const override;

		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override
		{
			return std::make_unique<FunctionDeclaration>(*this);
		}

		void addArgument(Variable::VariableSignature signature);

		std::unique_ptr<Type::IValue> operator()(const Type::Args& arguments) override final;
		
		void indexe() override final;
		std::unique_ptr<Type::IValue> interpret() override final;

		void setReturnType(CppUtils::Type::TypeId returnType)
		{
			m_returnType = std::move(returnType);
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return m_returnType;
		}
		
	private:
		std::vector<Variable::VariableSignature> m_arguments;
		CppUtils::Type::TypeId m_returnType;
	};

	std::ostream& operator<<(std::ostream& os, const FunctionDeclaration& functionDeclaration);
}
