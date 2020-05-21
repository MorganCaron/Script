#include <Language/AST/Scope/Type/Value.hpp>

namespace Language::AST::Scope::Type
{
	Value* Value::operator+(const Value& rhs) const
	{
		static_cast<void>(rhs);
		throw std::runtime_error("Utilisation incorrecte de l operateur +");
		return nullptr;
	}
	Value* Value::operator-(const Value& rhs) const
	{
		static_cast<void>(rhs);
		throw std::runtime_error("Utilisation incorrecte de l operateur -");
		return nullptr;
	}
	Value* Value::operator*(const Value& rhs) const
	{
		static_cast<void>(rhs);
		throw std::runtime_error("Utilisation incorrecte de l operateur *");
		return nullptr;
	}
	Value* Value::operator/(const Value& rhs) const
	{
		static_cast<void>(rhs);
		throw std::runtime_error("Utilisation incorrecte de l operateur /");
		return nullptr;
	}
	Value* Value::operator%(const Value& rhs) const
	{
		static_cast<void>(rhs);
		throw std::runtime_error("Utilisation incorrecte de l operateur %");
		return nullptr;
	}
	bool Value::operator==(const Value& rhs) const
	{
		static_cast<void>(rhs);
		return false;
	}
	bool Value::operator!=(const Value& rhs) const
	{
		static_cast<void>(rhs);
		return !(*this == rhs);
	}
	bool Value::operator<=(const Value& rhs) const
	{
		static_cast<void>(rhs);
		throw std::runtime_error("Utilisation incorrecte de l operateur <=");
		return false;
	}
	bool Value::operator>=(const Value& rhs) const
	{
		static_cast<void>(rhs);
		throw std::runtime_error("Utilisation incorrecte de l operateur >=");
		return false;
	}
	bool Value::operator<(const Value& rhs) const
	{
		static_cast<void>(rhs);
		throw std::runtime_error("Utilisation incorrecte de l operateur <");
		return false;
	}
	bool Value::operator>(const Value& rhs) const
	{
		static_cast<void>(rhs);
		throw std::runtime_error("Utilisation incorrecte de l operateur >");
		return false;
	}
}
