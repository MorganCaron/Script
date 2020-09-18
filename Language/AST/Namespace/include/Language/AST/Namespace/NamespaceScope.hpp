#pragma once

#include <CppUtils.hpp>

#include <Language/AST/Object/ObjectScope.hpp>

namespace Language::AST::Namespace
{
	constexpr static const Scope::ScopeType NamespaceScopeType = 4;

	class NamespaceDeclaration;
	class NamespaceScope: public Object::ObjectScope
	{
	public:
		NamespaceScope(BaseScope* scope = nullptr, Scope::ScopeType scopeType = NamespaceScopeType):
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
			ObjectScope::operator=(rhs);
			/*
			for (const auto &[key, value] : rhs.m_dlls)
				importDll(key);
			*/
			return *this;
		}
		NamespaceScope &operator=(NamespaceScope&&) noexcept = default;

		[[nodiscard]] inline bool namespaceExists(std::string_view name) const
		{
			if (m_namespaces.find(name.data()) != m_namespaces.end())
				return true;
			if (hasScope())
				return dynamic_cast<const NamespaceScope&>(getScope().findScope(getType())).namespaceExists(name);
			return false;
		}

		inline void addNamespace(std::string_view name, std::unique_ptr<NamespaceDeclaration>&& namespaceDeclaration)
		{
			m_namespaces[name.data()] = std::move(namespaceDeclaration);
		}

		inline void resetNamespaces() noexcept
		{
			m_namespaces.clear();
		}

		[[nodiscard]] inline const std::unordered_map<std::string, std::unique_ptr<NamespaceDeclaration>>& getNamespaces() const noexcept
		{
			return m_namespaces;
		}

		[[nodiscard]] inline const NamespaceDeclaration& getNamespace(std::string_view name) const
		{
			if (m_namespaces.find(name.data()) != m_namespaces.end())
				return *m_namespaces.at(name.data());
			if (!hasScope())
				throw std::runtime_error{"Unknown namespace "s + name.data() + "."};
			return dynamic_cast<const NamespaceScope&>(getScope().findScope(getType())).getNamespace(name);
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
		using DllFunctionType = Type::IValue* (CALLBACK*)(const Type::Args&);

		std::unordered_map<std::string, std::unique_ptr<NamespaceDeclaration>> m_namespaces;
		// std::unordered_map<std::string, std::unique_ptr<CppUtils::External::DynamicLibrary>> m_dlls;
	};
}
