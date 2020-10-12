#pragma once

#include <CppUtils.hpp>

#include <Language/AST/Function/FunctionScope.hpp>

namespace Language::AST::Object
{
	class Instance:
		public CppUtils::Type::Named,
		public Function::FunctionScope
	{
	public:
		Instance() = default;
		Instance(const Instance&) = default;
		Instance(Instance&&) noexcept = default;
		virtual ~Instance() = default;
		Instance& operator=(const Instance&) = default;
		Instance& operator=(Instance&&) noexcept = default;
		
		Instance(std::string name, const Function::FunctionScope& functionScope):
			CppUtils::Type::Named{std::move(name)},
			Function::FunctionScope{functionScope},
			m_constructor{nullptr}
		{}

		bool operator==(const Instance& rhs) const
		{
			if (getName() != rhs.getName())
				return false;
			return Variable::VariableScope::operator==(rhs);
		}

		void setConstructor(Function::FunctionType constructor)
		{
			m_constructor = std::move(constructor);
		}

		void callConstructor(const Type::Args& arguments)
		{
			m_constructor(arguments);
		}

	private:
		Function::FunctionType m_constructor;
	};
}
