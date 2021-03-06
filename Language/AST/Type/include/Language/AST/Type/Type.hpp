#pragma once

#include <memory>
#include <vector>
#include <functional>

#include <CppUtils.hpp>

namespace Language::AST::Type
{
	class DLL_PUBLIC IValue
	{
	public:
		virtual ~IValue() = default;
		[[nodiscard]] virtual bool isType(const CppUtils::Type::TypeId& type) const = 0;
		[[nodiscard]] virtual const CppUtils::Type::TypeId& getType() const = 0;
		[[nodiscard]] virtual std::unique_ptr<IValue> cloneValue() const = 0;
		[[nodiscard]] virtual bool isEqual(const std::unique_ptr<IValue>& value) const = 0;
	};

	template <typename TargetType>
	[[nodiscard]] std::unique_ptr<TargetType> ensureType(const std::unique_ptr<IValue>& value)
	{
		if (!value->isType(TargetType::TypeId))
			throw std::runtime_error{"Type incorrect. Type attendu: "s + TargetType::TypeId.name.data()};
		return std::make_unique<TargetType>(*static_cast<TargetType*>(value.get()));
	}

	template<const char* Typename, typename Storage>
	class DLL_PUBLIC Type final: public IValue
	{
	public:
		static constexpr auto TypeId = CppUtils::Type::TypeId{Typename};
		using StorageType = Storage;

		explicit Type(Storage value):
			m_value{std::move(value)}
		{}

		[[nodiscard]] bool isType(const CppUtils::Type::TypeId& type) const noexcept override final
		{
			return (TypeId == type);
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getType() const noexcept override final
		{
			return TypeId;
		}

		[[nodiscard]] std::unique_ptr<IValue> cloneValue() const override final
		{
			return std::make_unique<Type<Typename, Storage>>(*this);
		}

		[[nodiscard]] inline Storage& getValue() noexcept
		{
			return m_value;
		}

		[[nodiscard]] inline const Storage& getValue() const noexcept
		{
			return m_value;
		}

		[[nodiscard]] bool isEqual(const std::unique_ptr<IValue>& iValue) const override final
		{
			if (!iValue->isType(getType()))
				return false;
			const auto value = ensureType<Type<Typename, Storage>>(iValue)->getValue();
			return (value == m_value);
		}

	protected:
		Storage m_value;
	};

	using Args = std::vector<std::unique_ptr<IValue>>;
}
