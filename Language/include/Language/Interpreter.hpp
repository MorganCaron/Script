#pragma once

#include <memory>

#include <Language/Scope/Type/Value.hpp>

namespace Language
{
	class Interpreter
	{
	public:
		virtual ~Interpreter() = default;
		virtual std::unique_ptr<Scope::Type::Value> interpret() = 0;
	};
}
