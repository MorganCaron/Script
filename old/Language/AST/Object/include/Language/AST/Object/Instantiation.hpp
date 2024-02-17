#pragma once

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/NormalScope.hpp>
#include <Language/AST/Object/Instance.hpp>

namespace Script::Language::AST::Object
{
	class Instantiation final:
		public CppUtils::Type::Named,
		public Core::InstructionContainer,
		public Scope::NormalScope
	{
	public:
		static constexpr auto Type = CppUtils::Type::Token{"Instantiation"};

		explicit Instantiation(std::string name, Scope::NormalScope* scope):
			CppUtils::Type::Named{std::move(name)},
			Core::InstructionContainer{Type},
			Scope::NormalScope{scope}
		{}
		virtual ~Instantiation() = default;
		
		std::unique_ptr<AST::Type::IValue> interpret() override final;

		[[nodiscard]] const CppUtils::Type::Token& getReturnType() const override final
		{
			static const auto type = CppUtils::Type::Token{getName()};
			return type;
		}
	};
}
