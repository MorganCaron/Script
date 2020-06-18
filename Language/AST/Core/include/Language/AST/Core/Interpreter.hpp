#pragma once

#include <memory>

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Core
{
	class Interpreter
	{
	public:
		virtual ~Interpreter() = default;
		virtual void indexe() {};
		virtual std::unique_ptr<Type::IValue> interpret() = 0;
	};
}
