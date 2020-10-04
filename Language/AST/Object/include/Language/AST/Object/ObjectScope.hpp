#pragma once

#include <Language/AST/Function/FunctionScope.hpp>
#include <Language/AST/Object/Class.hpp>

namespace Language::AST::Object
{
	constexpr static const Scope::ScopeType ObjectScopeType = 3;

	class ObjectScope: public Function::FunctionScope
	{
	public:
		explicit ObjectScope(BaseScope* scope = nullptr, Scope::ScopeType scopeType = ObjectScopeType):
			Function::FunctionScope{scope, scopeType}
		{}
		ObjectScope(const ObjectScope& src):
			Function::FunctionScope{src}
		{
			for (const auto& [key, value] : src.getClasses())
				addClass(key, std::make_unique<Class>(*value));
		}
		ObjectScope(ObjectScope&&) noexcept = default;
		virtual ~ObjectScope() = default;
		ObjectScope& operator=(const ObjectScope& rhs)
		{
			Function::FunctionScope::operator=(rhs);
			for (const auto& [key, value] : rhs.getClasses())
				addClass(key, std::make_unique<Class>(*value));
			return *this;
		}
		ObjectScope& operator=(ObjectScope&&) noexcept = default;

		inline void merge(ObjectScope& objectScope)
		{
			Function::FunctionScope::merge(objectScope);
			for (auto&& [name, classPrototype] : objectScope.m_classes)
				addClass(name, std::move(classPrototype));
			objectScope.clearClasses();
		}

		[[nodiscard]] inline bool classExists(std::string_view name) const
		{
			if (m_classes.find(name.data()) != m_classes.end())
				return true;
			if (hasScope())
				return dynamic_cast<const ObjectScope&>(getScope().findScope(getType())).classExists(name);
			return false;
		}

		inline void addClass(std::string_view name, std::unique_ptr<Class>&& classPrototype)
		{
			if (m_classes.find(name.data()) != m_classes.end())
				throw std::runtime_error{"Class "s + name.data() + " already exists."};
			m_classes[name.data()] = std::move(classPrototype);
		}

		inline void clearClasses() noexcept
		{
			m_classes.clear();
		}

		[[nodiscard]] inline const std::unordered_map<std::string, std::unique_ptr<Class>>& getClasses() const noexcept
		{
			return m_classes;
		}

		[[nodiscard]] inline const Class& getClass(std::string_view name) const
		{
			if (m_classes.find(name.data()) != m_classes.end())
				return *m_classes.at(name.data());
			if (!hasScope())
				throw std::runtime_error{"Unknown class "s + name.data() + "."};
			return dynamic_cast<const ObjectScope&>(getScope().findScope(getType())).getClass(name);
		}

		[[nodiscard]] inline std::unique_ptr<Type::Instance> instantiate(std::string_view name, AST::Type::Args& arguments) const
		{
			return getClass(name).instantiate(arguments);
		}

	private:
		std::unordered_map<std::string, std::unique_ptr<Class>> m_classes;
	};
}
