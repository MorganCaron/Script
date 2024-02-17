#pragma once

#include <stack>
#include <type_traits>
#include <functional>

#include <Script/Language/VM/Operations.hpp>
#include <CppUtils/Language/Interpreter/VM.hpp>

namespace Script::Language::VM
{
	using namespace std::literals;
	using namespace Type::Literals;

	using Operation = std::function<void(Cursor&, RegisterFile&, std::stack<Value>&)>;

	class VM final
	{
	public:
		VM():
			m_vm{{
				{ "HALT"_token, Operations::halt },
				{ "NOP"_token, Operations::nop },
				{ "JUMP"_token, Operations::jump },
				{ "PUSH"_token, Operations::push },
				{ "POP"_token, Operations::pop }
			}}
		{}

		void run(std::span<const Instruction> instructions, Context& context) const
		{
			m_vm.run(instructions, context);
		}

	private:
		Interpreter::VM<Instruction, Context> m_vm;
	};
}
