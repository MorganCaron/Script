#pragma once

#include <CppUtils.hpp>

#include "FunctionScope.hpp"

namespace Language::Scope::Type
{
	using ConstructorType = ITFunction<void(Args&)>;

	class Object:
		public Value,
		public CppUtils::Type::Named,
		public FunctionScope
	{
	public:
		constexpr static const auto type = "Object"sv;

		Object(std::string name, BaseScope* scope = nullptr):
			Value{type.data()},
			CppUtils::Type::Named{std::move(name)},
			FunctionScope{scope},
			m_constructor{nullptr}
		{}
		Object(const Object& src):
			Value{src},
			CppUtils::Type::Named{src},
			FunctionScope{src}
		{
			if (src.m_constructor)
				moveConstructor(src.m_constructor->cloneFunction());
		}
		Object(Object&&) noexcept = default;
		Object& operator=(const Object& rhs)
		{
			Value::operator=(rhs);
			Named::operator=(rhs);
			FunctionScope::operator=(rhs);
			if (rhs.m_constructor)
				moveConstructor(rhs.m_constructor->cloneFunction());
			return *this;
		}
		Object& operator=(Object&&) noexcept = default;
		virtual ~Object() = default;
		
		std::unique_ptr<Value> cloneValue() const override
		{
			return std::make_unique<Object>(*this);
		}

		void moveConstructor(std::unique_ptr<ConstructorType>&& constructor)
		{
			m_constructor = std::move(constructor);
		}

		void callConstructor(Args& arguments)
		{
			if (m_constructor)
				(*m_constructor)(arguments);
		}

	private:
		std::unique_ptr<ConstructorType> m_constructor;
	};
}
