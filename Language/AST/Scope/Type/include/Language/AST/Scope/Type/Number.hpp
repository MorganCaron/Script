#pragma once

#include <cmath>
#include <string_view>

#include <Language/AST/Scope/Type/Value.hpp>

namespace Language::AST::Scope::Type
{
	class DLL_PUBLIC Number: public Value
	{
	public:
		constexpr static const auto type = "Number"sv;
		
		Number(const double& value = 0): Value{type.data()}, m_value{value}
		{}
		virtual ~Number() = default;

		std::unique_ptr<Value> cloneValue() const override
		{
			return std::make_unique<Number>(*this);
		}
		inline double getValue() const noexcept
		{
			return m_value;
		}
		std::ostream& print(std::ostream& os) const override
		{
			return os << m_value;
		}

		Value* operator+(const Value& rhs) const override;
		Value* operator-(const Value& rhs) const override;
		Value* operator*(const Value& rhs) const override;
		Value* operator/(const Value& rhs) const override;
		Value* operator%(const Value& rhs) const override;
		bool operator==(const Value& rhs) const override;

	private:
		double m_value;
	};

	std::ostream& operator<<(std::ostream& os, const Number& number);
}
