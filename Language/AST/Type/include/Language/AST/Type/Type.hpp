#pragma once

#include <memory>
#include <vector>
#include <functional>

#include <CppUtils.hpp>

using namespace std::literals::string_view_literals;

namespace Language::AST::Type
{
	class DLL_PUBLIC IValue
	{
	public:
		virtual ~IValue() = default;
		virtual bool isType(const std::size_t typeId) const = 0;
		virtual std::string_view getTypeName() const = 0;
		virtual std::unique_ptr<IValue> cloneValue() const = 0;
	};

	template <typename TargetType>
	std::unique_ptr<TargetType> ensureType(const std::unique_ptr<IValue>& value)
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
		static constexpr const auto TypeId = CppUtils::Hash::constexprHash(Tag::Name);

		explicit Type(Storage&& value):
			m_value{std::forward<Storage>(value)}
		{}

		bool isType(const std::size_t typeId) const noexcept override final
		{
			return (typeId == TypeId);
		}

		std::string_view getTypeName() const noexcept override final
		{
			return Tag::Name;
		}

		std::unique_ptr<IValue> cloneValue() const override final
		{
			return std::make_unique<Type<Tag, Storage>>(*this);
		}

		inline const Storage& getValue() const noexcept
		{
			return m_value;
		}

	protected:
		Storage m_value;
	};

	using Args = std::vector<std::unique_ptr<IValue>>;
}
