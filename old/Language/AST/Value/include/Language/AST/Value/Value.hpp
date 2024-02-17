#pragma once

#include <Language/AST/Core/Instruction.hpp>

namespace Script::Language::AST::Value
{
	template<class T>
	class Value: public Core::Instruction
	{
	public:
		explicit Value(std::unique_ptr<T>&& value, CppUtils::Type::Token type):
			Core::Instruction{std::move(type)},
			m_value{std::make_unique<T>(*value)}
		{}
		Value(const Value& src):
			Core::Instruction{src},
			m_value{std::make_unique<T>(src.getValue())}
		{}
		Value(Value&&) noexcept = default;
		Value& operator=(const Value& rhs)
		{
			Core::Instruction::operator=(rhs);
			m_value = std::make_unique<T>(*rhs.getValue());
			return *this;
		}
		Value& operator=(Value&&) noexcept = default;

		[[nodiscard]] const T& getValue() const noexcept
		{
			return *m_value;
		}

		[[nodiscard]] std::unique_ptr<T> cloneValue() const
		{
			return std::make_unique<T>(m_value);
		}

		std::unique_ptr<Type::IValue> interpret() override final
		{
			return m_value->cloneValue();
		}

		[[nodiscard]] const CppUtils::Type::Token& getReturnType() const override final
		{
			return T::Token;
		}

	private:
		std::unique_ptr<T> m_value;
	};
}
