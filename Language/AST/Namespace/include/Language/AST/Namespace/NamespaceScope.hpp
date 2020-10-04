#pragma once

#include <CppUtils.hpp>

#include <Language/AST/Object/ObjectScope.hpp>

namespace Language::AST::Namespace
{
	using DllFunctionType = Type::IValue* (CALLBACK*)(const Type::Args&);

	constexpr static const Scope::ScopeType NamespaceScopeType = 4;

	class NamespaceScope: public Object::ObjectScope
	{
	public:
		explicit NamespaceScope(BaseScope* scope = nullptr, Scope::ScopeType scopeType = NamespaceScopeType):
			Object::ObjectScope{scope, scopeType}
		{}
		NamespaceScope(const NamespaceScope& src):
			Object::ObjectScope{src}
		{
			/*
			for (const auto& [key, value] : src.m_dlls)
				importDll(key);
			*/
		}
		NamespaceScope(NamespaceScope&&) noexcept = default;
		virtual ~NamespaceScope() = default;
		NamespaceScope& operator=(const NamespaceScope& rhs)
		{
			Object::ObjectScope::operator=(rhs);
			/*
			for (const auto &[key, value] : rhs.m_dlls)
				importDll(key);
			*/
			return *this;
		}
		NamespaceScope &operator=(NamespaceScope&&) noexcept = default;

		inline void merge(NamespaceScope& namespaceScope)
		{
			Object::ObjectScope::merge(namespaceScope);
			for (auto&& [namespaceId, newNamespace] : namespaceScope.m_namespaces)
				if (m_namespaces.find(namespaceId) != m_namespaces.end())
					m_namespaces[namespaceId]->merge(*newNamespace);
				else
					addNamespace(namespaceId, std::move(newNamespace));
			namespaceScope.clearNamespaces();
		}

		[[nodiscard]] inline bool namespaceExists(const CppUtils::Type::TypeId& namespaceId) const
		{
			if (m_namespaces.find(namespaceId) != m_namespaces.end())
				return true;
			if (hasScope())
				return dynamic_cast<const NamespaceScope&>(getScope().findScope(getType())).namespaceExists(namespaceId);
			return false;
		}

		inline void addNamespace(const CppUtils::Type::TypeId& namespaceId, std::unique_ptr<NamespaceScope>&& newNamespace)
		{
			if (m_namespaces.find(namespaceId) != m_namespaces.end())
				m_namespaces[namespaceId]->merge(*newNamespace);
			else
				m_namespaces[namespaceId] = std::move(newNamespace);
		}

		inline void addNamespaces(std::unordered_map<CppUtils::Type::TypeId, std::unique_ptr<NamespaceScope>, CppUtils::Type::TypeId::hash_fn> namespaceScopes)
		{
			for (auto&& [namespaceId, namespaceScope] : namespaceScopes)
				addNamespace(namespaceId, std::move(namespaceScope));
		}

		inline void clearNamespaces() noexcept
		{
			m_namespaces.clear();
		}

		[[nodiscard]] inline const std::unordered_map<CppUtils::Type::TypeId, std::unique_ptr<NamespaceScope>, CppUtils::Type::TypeId::hash_fn>& getNamespaces() const noexcept
		{
			return m_namespaces;
		}

		[[nodiscard]] inline NamespaceScope& getNamespace(const CppUtils::Type::TypeId& namespaceId)
		{
			if (m_namespaces.find(namespaceId) != m_namespaces.end())
				return *m_namespaces.at(namespaceId);
			if (!hasScope())
				throw std::runtime_error{"Unknown namespace "s + namespaceId.name.data() + "."};
			return dynamic_cast<NamespaceScope&>(getScope().findScope(getType())).getNamespace(namespaceId);
		}
		
		[[nodiscard]] inline const NamespaceScope& getNamespace(const CppUtils::Type::TypeId& namespaceId) const
		{
			if (m_namespaces.find(namespaceId) != m_namespaces.end())
				return *m_namespaces.at(namespaceId);
			if (!hasScope())
				throw std::runtime_error{"Unknown namespace "s + namespaceId.name.data() + "."};
			return dynamic_cast<const NamespaceScope&>(getScope().findScope(getType())).getNamespace(namespaceId);
		}

		void importDll([[maybe_unused]] std::string_view filename)
		{
			/*
			auto& dll = m_dlls[filename.data()] = std::make_unique<CppUtils::External::DynamicLibrary>(filename);

			auto pluginInformations = dll->getSymbol<PluginInformations*>("pluginInformations");
			std::cout << "Name: " << pluginInformations->name << '\n'
				<< "Version: " << pluginInformations->version << std::endl;
			
			auto dllFunction = dll->getSymbol<DllFunctionType>("create"s + filename.data());
			auto function = std::function<std::unique_ptr<Value>(const Args&)>([dllFunction](const Args& args) {
				return std::unique_ptr<Type::IValue>(dllFunction(args));
			});
			addFunction(filename, std::make_unique<Function>(function));
			*/
		}

	private:
		std::unordered_map<CppUtils::Type::TypeId, std::unique_ptr<NamespaceScope>, CppUtils::Type::TypeId::hash_fn> m_namespaces;
		// std::unordered_map<std::string, std::unique_ptr<CppUtils::External::DynamicLibrary>> m_dlls;
	};
}
