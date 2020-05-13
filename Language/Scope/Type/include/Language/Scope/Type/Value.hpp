#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>

using namespace std::literals::string_view_literals;

namespace Language::Scope::Type
{
	using ValueType = std::string_view;

	class Value
	{
	public:
		explicit Value(ValueType valueType): m_type{valueType}
		{}
		virtual ~Value() = default;

		virtual std::unique_ptr<Value> cloneValue() const
		{
			throw std::runtime_error("L'objet " + m_type + " n'a pas été bien conçu. Il doit être cloneable.");
			return std::make_unique<Value>(*this);
		}

		inline ValueType getType() const noexcept
		{
			return m_type;
		}

		virtual std::ostream& print(std::ostream& os) const
		{
			return os;
		}

		virtual Value* operator+(const Value& rhs) const;
		virtual Value* operator-(const Value& rhs) const;
		virtual Value* operator*(const Value& rhs) const;
		virtual Value* operator/(const Value& rhs) const;
		virtual Value* operator%(const Value& rhs) const;
		virtual bool operator==(const Value& rhs) const;
		virtual bool operator!=(const Value& rhs) const;
		virtual bool operator<=(const Value& rhs) const;
		virtual bool operator>=(const Value& rhs) const;
		virtual bool operator<(const Value& rhs) const;
		virtual bool operator>(const Value& rhs) const;

	private:
		std::string m_type;
	};

	inline std::ostream& operator<<(std::ostream& os, const Value& value)
	{
		return value.print(os);
	}

	using Args = std::vector<std::unique_ptr<Value>>;

	template <typename To>
	std::unique_ptr<To> ensureType(const std::unique_ptr<Value>& value)
	{
		return std::make_unique<To>(*static_cast<To*>(value.get()));
	};
}
