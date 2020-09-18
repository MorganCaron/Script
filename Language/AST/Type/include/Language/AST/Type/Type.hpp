#pragma once

#include <memory>
#include <vector>
#include <functional>

#include <CppUtils.hpp>

namespace Language::AST::Type
{
	constexpr const auto VoidType = CppUtils::Type::TypeId{""};
	
	class DLL_PUBLIC IValue
	{
	public:
		virtual ~IValue() = default;
		[[nodiscard]] virtual bool isType(const CppUtils::Type::TypeId& type) const = 0;
		[[nodiscard]] virtual std::string_view getTypeName() const = 0;
		[[nodiscard]] virtual std::unique_ptr<IValue> cloneValue() const = 0;
	};

	template <typename TargetType>
	[[nodiscard]] std::unique_ptr<TargetType> ensureType(const std::unique_ptr<IValue>& value)
	{
		if (!value->isType(TargetType::TypeId))
			throw std::runtime_error{"Type incorrect. Type attendu: "s + TargetType::TagType::Name.data()};
		return std::make_unique<TargetType>(*static_cast<TargetType*>(value.get()));
	}

	template<typename Tag, typename Storage>
	class DLL_PUBLIC Type final: public IValue
	{
	public:
		using TagType = Tag;
		using StorageType = Storage;
		static constexpr const auto TypeId = CppUtils::Type::TypeId{Tag::Name};

		explicit Type(Storage value):
			m_value{std::move(value)}
		{}

		[[nodiscard]] bool isType(const CppUtils::Type::TypeId& type) const noexcept override final
		{
			return (TypeId == type);
		}

		[[nodiscard]] std::string_view getTypeName() const noexcept override final
		{
			return TypeId.name;
		}

		[[nodiscard]] std::unique_ptr<IValue> cloneValue() const override final
		{
			return std::make_unique<Type<Tag, Storage>>(*this);
		}

		[[nodiscard]] inline Storage& getValue() noexcept
		{
			return m_value;
		}

	protected:
		Storage m_value;
	};

	using Args = std::vector<std::unique_ptr<IValue>>;
}
