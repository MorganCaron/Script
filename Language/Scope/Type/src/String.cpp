#include "Language/Scope/Type/String.hpp"

namespace Language::Scope::Type
{
	Value* String::operator+(const Value& rhs) const
	{
		if (rhs.getType() != "String")
			throw std::runtime_error{"L'operande a droite de l'operateur + doit etre un String."};
		return new String(m_value + dynamic_cast<const String&>(rhs).getValue());
	}
	bool String::operator==(const Value& rhs) const
	{
		return (m_value == dynamic_cast<const String&>(rhs).getValue());
	}

	std::ostream& operator<<(std::ostream& os, const String& string)
	{
		os << '"' << string.getValue().c_str() << '"';
		return os;
	}
}
