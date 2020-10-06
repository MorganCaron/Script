#pragma once

#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Object/Type.hpp>
#include <Language/AST/Type/Boolean.hpp>

namespace Language::AST::Object
{
	class Class final:
		public Instance,
		public Core::Instruction,
		public Core::InstructionContainer
	{
	public:
		static constexpr const auto Type = CppUtils::Type::TypeId{"Class"};
		static constexpr const auto Keyword = "class"sv;

		explicit Class(std::string name, Scope::BaseScope* scope = nullptr):
			Instance{std::move(name), scope},
			Core::Instruction{Type}
		{}

		[[nodiscard]] std::unique_ptr<Core::Instruction> cloneInstruction() const override final
		{
			return std::make_unique<Class>(*this);
		}

		[[nodiscard]] std::unique_ptr<Type::Instance> instantiate(const AST::Type::Args& arguments) const
		{
			auto instance = std::make_unique<Type::Instance>(*this);
			instance->getValue().callConstructor(arguments);
			return instance;
		}
		
		void indexe() override final;

		std::unique_ptr<AST::Type::IValue> interpret() override final
		{
			indexe();
			return std::make_unique<AST::Type::Boolean>(false);
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return AST::Type::VoidType;
		}
	};
}
