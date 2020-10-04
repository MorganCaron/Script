#pragma once

#include <CppUtils.hpp>

#include <Language/AST/Function/FunctionScope.hpp>

namespace Language::AST::Object
{
	using ConstructorType = Function::ITFunction<void(const Type::Args&)>;

	class Instance:
		public CppUtils::Type::Named,
		public Function::FunctionScope
	{
	public:
		explicit Instance(std::string name, BaseScope* scope = nullptr):
			CppUtils::Type::Named{std::move(name)},
			Function::FunctionScope{scope},
			m_constructor{nullptr}
		{}
		Instance(const Instance& src):
			CppUtils::Type::Named{src},
			Function::FunctionScope{src}
		{
			if (src.m_constructor)
				setConstructor(src.m_constructor->cloneFunction());
		}
		Instance(Instance&&) noexcept = default;
		Instance& operator=(const Instance& rhs)
		{
			Named::operator=(rhs);
			FunctionScope::operator=(rhs);
			if (rhs.m_constructor)
				setConstructor(rhs.m_constructor->cloneFunction());
			return *this;
		}
		Instance& operator=(Instance&&) noexcept = default;
		virtual ~Instance() = default;

		bool operator==(const Instance& rhs) const
		{
			if (getName() != rhs.getName())
				return false;
			return Variable::VariableScope::operator==(rhs);
		}

		void setConstructor(std::unique_ptr<ConstructorType>&& constructor)
		{
			m_constructor = std::move(constructor);
		}

		void callConstructor(const Type::Args& arguments)
		{
			if (m_constructor)
				(*m_constructor)(arguments);
		}

	private:
		std::unique_ptr<ConstructorType> m_constructor;
	};
}
