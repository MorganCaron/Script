#pragma once

#include <functional>
#include <unordered_map>

#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Namespace/NamespaceScope.hpp>

namespace Language
{
	class ASTRoot final:
		public AST::Core::InstructionContainer,
		public AST::Namespace::NamespaceScope
	{
	public:
		ASTRoot();
		explicit ASTRoot(std::string src);

		void parse(std::string_view src, bool verbose = false);
		std::unique_ptr<AST::Type::IValue> interpret() override final;

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final;

	private:
		void initNativeParsers();
	};
}
