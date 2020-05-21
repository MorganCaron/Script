#pragma once

#include <memory>

#include <Language/AST/Scope/Type/Value.hpp>

namespace Language::AST
{
	class Interpreter
	{
	public:
		virtual ~Interpreter() = default;
		virtual std::unique_ptr<Scope::Type::Value> interpret() = 0;
	};
}
