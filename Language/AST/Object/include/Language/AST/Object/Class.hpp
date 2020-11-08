#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Function/FunctionScope.hpp>
#include <Language/AST/Object/Instance.hpp>
#include <Language/AST/Object/Type.hpp>
#include <Language/AST/Type/Void.hpp>

namespace Language::AST::Object
{
	class Class final:
		public CppUtils::Type::Named,
		public Core::InstructionContainer,
		public Function::FunctionScope
	{
	public:
		static constexpr auto Type = CppUtils::Type::TypeId{"Class"};
		static constexpr auto Keyword = "class"sv;

		explicit Class(std::string name, Scope::NormalScope* scope = nullptr):
			Named{std::move(name)},
			Core::InstructionContainer{Type},
			Function::FunctionScope{scope}
		{}

		void indexe() override final;

		std::unique_ptr<AST::Type::IValue> interpret() override final
		{
			return std::make_unique<AST::Type::Void>(nullptr);
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return AST::Type::Void::TypeId;
		}
	};
}
