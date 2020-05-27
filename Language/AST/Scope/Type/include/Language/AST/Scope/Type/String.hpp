#pragma once

#include <Language/AST/Scope/Type/Value.hpp>

namespace Language::AST::Scope::Type
{
	class DLL_PUBLIC String: public Value
	{
	public:
		static constexpr const auto type = "String"sv;

		String(std::string value = ""): Value{type.data()}, m_value{std::move(value)}
		{}
		virtual ~String() = default;

		std::unique_ptr<Value> cloneValue() const override
		{
			return std::make_unique<String>(*this);
		}
		inline std::string getValue() const noexcept
		{
			return m_value;
		}
		std::ostream& print(std::ostream& os) const override
		{
			return os << m_value;
		}

		Value* operator+(const Value& rhs) const override;
		bool operator==(const Value& rhs) const override;

	private:
		std::string m_value;
	};

	std::ostream& operator<<(std::ostream& os, const String& string);
}
