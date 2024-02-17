#pragma once

#include <CppUtils.hpp>

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/AST/Object/ObjectScope.hpp>

namespace Script::Language::AST::Namespace
{
	// using DllFunctionType = Type::IValue* (CALLBACK*)(const Type::Args&);

	class NamespaceScope: public Object::ObjectScope
	{
	public:
		constexpr static const Scope::ScopeType Type = 4;

		explicit NamespaceScope(NormalScope* scope = nullptr, Scope::ScopeType scopeType = Type):
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

		void merge(NamespaceScope& namespaceScope)
		{
			Object::ObjectScope::merge(namespaceScope);
			for (auto&& [namespaceId, newNamespace] : namespaceScope.m_namespaces)
				if (m_namespaces.find(namespaceId) != m_namespaces.end())
					m_namespaces[namespaceId]->merge(*newNamespace);
				else
					addNamespace(namespaceId, std::move(newNamespace));
			namespaceScope.clearNamespaces();
		}

		[[nodiscard]] bool namespaceExists(const CppUtils::Type::Token& namespaceId) const
		{
			if (m_namespaces.find(namespaceId) != m_namespaces.end())
				return true;
			if (hasParentScope())
				return dynamic_cast<const NamespaceScope&>(getParentScope().findScope(getType())).namespaceExists(namespaceId);
			return false;
		}

		void addNamespace(const CppUtils::Type::Token& namespaceId, std::unique_ptr<NamespaceScope>&& newNamespace)
		{
			if (m_namespaces.find(namespaceId) != m_namespaces.end())
				m_namespaces[namespaceId]->merge(*newNamespace);
			else
				m_namespaces[namespaceId] = std::move(newNamespace);
		}

		void addNamespaces(std::unordered_map<CppUtils::Type::Token, std::unique_ptr<NamespaceScope>, CppUtils::Type::Token::hash_fn> namespaceScopes)
		{
			for (auto&& [namespaceId, namespaceScope] : namespaceScopes)
				addNamespace(namespaceId, std::move(namespaceScope));
		}

		void clearNamespaces() noexcept
		{
			m_namespaces.clear();
		}

		[[nodiscard]] const std::unordered_map<CppUtils::Type::Token, std::unique_ptr<NamespaceScope>, CppUtils::Type::Token::hash_fn>& getNamespaces() const noexcept
		{
			return m_namespaces;
		}

		[[nodiscard]] NamespaceScope& getNamespace(const CppUtils::Type::Token& namespaceId)
		{
			if (m_namespaces.find(namespaceId) != m_namespaces.end())
				return *m_namespaces.at(namespaceId);
			if (!hasParentScope())
				throw std::runtime_error{"Unknown namespace "s + namespaceId.name.data() + "."};
			return dynamic_cast<NamespaceScope&>(getParentScope().findScope(getType())).getNamespace(namespaceId);
		}
		
		[[nodiscard]] const NamespaceScope& getNamespace(const CppUtils::Type::Token& namespaceId) const
		{
			if (m_namespaces.find(namespaceId) != m_namespaces.end())
				return *m_namespaces.at(namespaceId);
			if (!hasParentScope())
				throw std::runtime_error{"Unknown namespace "s + namespaceId.name.data() + "."};
			return dynamic_cast<const NamespaceScope&>(getParentScope().findScope(getType())).getNamespace(namespaceId);
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

		std::vector<ParsingTools::NamedParser<ParsingTools::DeclarationParser>> declarationParsers;
		std::vector<ParsingTools::NamedParser<ParsingTools::InstructionParser>> instructionParsers;
		std::vector<ParsingTools::NamedParser<ParsingTools::ValueParser>> valueParsers;
		std::vector<ParsingTools::NamedParser<ParsingTools::OperatorParser>> operatorParsers;

	private:
		std::unordered_map<CppUtils::Type::Token, std::unique_ptr<NamespaceScope>, CppUtils::Type::Token::hash_fn> m_namespaces;
		// std::unordered_map<std::string, std::unique_ptr<CppUtils::External::DynamicLibrary>> m_dlls;
	};
}
