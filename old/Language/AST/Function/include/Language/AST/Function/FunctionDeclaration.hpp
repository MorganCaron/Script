#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Variable/VariableScope.hpp>
#include <Language/AST/Function/Function.hpp>

namespace Script::Language::AST::Function
{
	using namespace std::literals;
	
	class FunctionDeclaration final:
		public CppUtils::Type::Named,
		public Core::InstructionContainer,
		public Variable::VariableScope
	{
	public:
		static constexpr auto Type = CppUtils::Type::Token{"Function declaration"};
		static constexpr auto Keyword = "function"sv;
		
		explicit FunctionDeclaration(std::string name, Scope::NormalScope* scope);

		void addArgument(Variable::VariableSignature signature);

		std::unique_ptr<Type::IValue> executeFunction(const Type::Args& arguments);
		
		void indexe() override final;
		std::unique_ptr<Type::IValue> interpret() override final;

		void setReturnType(CppUtils::Type::Token returnType)
		{
			m_returnType = std::move(returnType);
		}

		[[nodiscard]] const CppUtils::Type::Token& getReturnType() const override final
		{
			return m_returnType;
		}
		
	private:
		std::vector<Variable::VariableSignature> m_arguments;
		CppUtils::Type::Token m_returnType;
	};

	std::ostream& operator<<(std::ostream& os, const FunctionDeclaration& functionDeclaration);
}
