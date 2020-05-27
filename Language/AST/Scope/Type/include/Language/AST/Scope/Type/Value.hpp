#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>

#include <External/DllExport.hpp>

using namespace std::literals::string_view_literals;

namespace Language::AST::Scope::Type
{
	class DLL_PUBLIC Value
	{
	public:
		explicit Value(std::string type): m_type{std::move(type)}
		{}
		virtual ~Value() = default;

		virtual std::unique_ptr<Value> cloneValue() const
		{
			throw std::runtime_error("L'objet " + m_type + " n'a pas été bien conçu. Il doit être cloneable.");
			return std::make_unique<Value>(*this);
		}

		inline std::string_view getType() const noexcept
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
		
		template <typename To>
		static std::unique_ptr<To> ensureType(const std::unique_ptr<Value>& value)
		{
			return std::make_unique<To>(*static_cast<To*>(value.get()));
		}

	private:
		std::string m_type;
	};

	inline std::ostream& operator<<(std::ostream& os, const Value& value)
	{
		return value.print(os);
	}

	struct Variable
	{
		Variable() = default;
		Variable(std::unique_ptr<Value>&& c_value, bool constant):
			value{std::move(c_value)},
			isConstant{constant}
		{}
		Variable(const Variable& src):
			value{src.value->cloneValue()},
			isConstant{src.isConstant}
		{}
		Variable(Variable&&) = default;
		Variable& operator=(const Variable& rhs)
		{
			value = rhs.value->cloneValue();
			isConstant = rhs.isConstant;
			return *this;
		}
		Variable& operator=(Variable&&) = default;

		std::unique_ptr<Value> value;
		bool isConstant;
	};

	using Args = std::vector<std::unique_ptr<Value>>;
}
