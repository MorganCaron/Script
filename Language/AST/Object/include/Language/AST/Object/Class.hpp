#pragma once

#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Object/Instance.hpp>
#include <Language/AST/Type/Number.hpp>

namespace Language::AST::Object
{
	class Class final:
		public Instance,
		public Core::Instruction,
		public Core::InstructionContainer
	{
	public:
		static constexpr const auto Type = "Class"sv;
		static constexpr const auto Keyword = "class"sv;

		explicit Class(std::string name, Scope::BaseScope* scope = nullptr):
			Instance{std::move(name), scope},
			Core::Instruction{std::string{Type}}
		{}
		Class(const Class& src);
		Class(Class&&) = default;
		virtual ~Class() = default;
		Class &operator=(const Class& rhs);
		Class &operator=(Class&&) = default;

		std::unique_ptr<Core::Instruction> cloneInstruction() const override final
		{
			return std::make_unique<Class>(*this);
		}
		
		void indexe() override final;
		std::unique_ptr<Type::IValue> interpret() override final;
	};
}
