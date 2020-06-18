#include <Language/AST/Type/Number.hpp>

namespace Language::AST::Type
{
	/*
	Value* Number::operator+(const Value& rhs) const
	{
		if (rhs.getType() != "Number")
			throw std::runtime_error{"L operande à droite de l'operateur + doit être un Number."};
		return new Number(m_value + dynamic_cast<const Number&>(rhs).getValue());
	}
	Value* Number::operator-(const Value& rhs) const
	{
		if (rhs.getType() != "Number")
			throw std::runtime_error{"L operande à droite de l'operateur - doit être un Number."};
		return new Number(m_value - dynamic_cast<const Number&>(rhs).getValue());
	}
	Value* Number::operator*(const Value& rhs) const
	{
		if (rhs.getType() != "Number")
			throw std::runtime_error{"L operande à droite de l'operateur * doit être un Number."};
		return new Number(m_value * dynamic_cast<const Number&>(rhs).getValue());
	}
	Value* Number::operator/(const Value& rhs) const
	{
		if (rhs.getType() != "Number")
			throw std::runtime_error{"L operande à droite de l'operateur / doit être un Number."};
		auto value = dynamic_cast<const Number&>(rhs).getValue();
		if (value == 0)
			std::runtime_error("Division par zero impossible.");
		return new Number(m_value / value);
	}
	Value* Number::operator%(const Value& rhs) const
	{
		if (rhs.getType() != "Number")
			throw std::runtime_error{"L operande à droite de l'operateur % doit être un Number."};
		auto value = dynamic_cast<const Number&>(rhs).getValue();
		if (value == 0)
			std::runtime_error("Division par zero impossible.");
		return new Number(std::fmod(m_value, value));
	}
	bool Number::operator==(const Value& rhs) const
	{
		if (rhs.getType() != "Number")
			throw std::runtime_error{"L operande à droite de l'operateur == doit être un Number."};
		return new Number(m_value == dynamic_cast<const Number&>(rhs).getValue());
	}

	std::ostream& operator<<(std::ostream& os, const Number& number)
	{
		os << number.getValue();
		return os;
	}
	*/
}
