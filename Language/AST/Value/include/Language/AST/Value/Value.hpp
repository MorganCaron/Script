#pragma once

#include <Language/AST/Core/Instruction.hpp>

namespace Language::AST::Value
{
	template<typename T>
	class Value: public Core::Instruction
	{
	public:
		explicit Value(std::unique_ptr<T>&& value, CppUtils::Type::TypeId type):
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

		[[nodiscard]] inline const T& getValue() const noexcept
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

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const override final
		{
			return T::TypeId;
		}

	private:
		std::unique_ptr<T> m_value;
	};
}
