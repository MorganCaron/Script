#pragma once

#include <CppUtils.hpp>

namespace Script::Language::VM::Operations
{
	void halt(Cursor& cursor, [[maybe_unused]] Context& context) noexcept
	{
		cursor.exit();
	}

	void nop(Cursor& cursor, [[maybe_unused]] Context& context) noexcept
	{
		++cursor.pos;
	}

	void jump(Cursor& cursor, [[maybe_unused]] Context& context)
	{
		const auto& parameters = cursor.getInstruction().parameters;

		cursor.pos = parameters.at(0).id;
	}

	void move(Cursor& cursor, Context& context)
	{
		const auto& parameters = cursor.getInstruction().parameters;
		auto& [registerFile, stack] = context;

		registerFile[parameters.at(0)] = registerFile.at(parameters.at(1));
		++cursor.pos;
	}
	
	void push(Cursor& cursor, Context& context)
	{
		const auto& parameters = cursor.getInstruction().parameters;
		auto& [registerFile, stack] = context;

		stack.emplace(registerFile.at(parameters.at(0)));
		++cursor.pos;
	}

	void pop(Cursor& cursor, Context& context)
	{
		const auto& parameters = cursor.getInstruction().parameters;
		auto& [registerFile, stack] = context;

		if (stack.size() == 0)
			throw std::runtime_error{"Stack underflow"};

		registerFile[parameters.at(0)] = stack.top();
		stack.pop();
		++cursor.pos;
	}
}
