#pragma once

#include <Language/AST/Function/FunctionScope.hpp>
#include <Language/AST/Object/Class.hpp>

namespace Script::Language::AST::Object
{
	constexpr static const Scope::ScopeType ObjectScopeType = 3;

	class ObjectScope: public Function::FunctionScope
	{
	public:
		explicit ObjectScope(NormalScope* scope = nullptr, Scope::ScopeType scopeType = ObjectScopeType):
			Function::FunctionScope{scope, scopeType}
		{}
		ObjectScope(const ObjectScope& src):
			Function::FunctionScope{src}
		{
			for (const auto& [key, value] : src.getClasses())
				addClass(key, std::make_unique<Type::Instance>(*value));
		}
		ObjectScope(ObjectScope&&) noexcept = default;
		virtual ~ObjectScope() = default;
		ObjectScope& operator=(const ObjectScope& rhs)
		{
			Function::FunctionScope::operator=(rhs);
			for (const auto& [key, value] : rhs.getClasses())
				addClass(key, std::make_unique<Type::Instance>(*value));
			return *this;
		}
		ObjectScope& operator=(ObjectScope&&) noexcept = default;

		void merge(ObjectScope& objectScope)
		{
			Function::FunctionScope::merge(objectScope);
			for (auto&& [name, classPrototype] : objectScope.m_classes)
				addClass(name, std::move(classPrototype));
			objectScope.clearClasses();
		}

		[[nodiscard]] bool classExists(std::string_view name) const
		{
			if (m_classes.find(name.data()) != m_classes.end())
				return true;
			if (hasParentScope())
				return dynamic_cast<const ObjectScope&>(getParentScope().findScope(getType())).classExists(name);
			return false;
		}

		void addClass(std::string_view name, std::unique_ptr<Type::Instance>&& classPrototype)
		{
			if (m_classes.find(name.data()) != m_classes.end())
				throw std::runtime_error{"Class "s + name.data() + " already exists."};
			m_classes[name.data()] = std::move(classPrototype);
		}

		void clearClasses() noexcept
		{
			m_classes.clear();
		}

		[[nodiscard]] const std::unordered_map<std::string, std::unique_ptr<Type::Instance>>& getClasses() const noexcept
		{
			return m_classes;
		}

		[[nodiscard]] const Type::Instance& getClass(std::string_view name) const
		{
			if (m_classes.find(name.data()) != m_classes.end())
				return *m_classes.at(name.data());
			if (!hasParentScope())
				throw std::runtime_error{"Unknown class "s + name.data() + "."};
			return dynamic_cast<const ObjectScope&>(getParentScope().findScope(getType())).getClass(name);
		}

		[[nodiscard]] std::unique_ptr<Type::Instance> instantiate(std::string_view name, const AST::Type::Args& arguments) const
		{
			auto instance = std::make_unique<Type::Instance>(getClass(name));
			instance->getValue()->callConstructor(arguments);
			return instance;
		}

	private:
		std::unordered_map<std::string, std::unique_ptr<Type::Instance>> m_classes;
	};
}
