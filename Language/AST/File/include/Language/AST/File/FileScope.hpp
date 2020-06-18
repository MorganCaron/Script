#pragma once

#include <CppUtils.hpp>

#include <Language/AST/Object/ObjectScope.hpp>

namespace Language::AST::File
{
	constexpr static const Scope::ScopeType FileScopeType = 4;

	class FileScope: public Object::ObjectScope
	{
	public:
		FileScope(BaseScope* scope = nullptr, Scope::ScopeType scopeType = FileScopeType):
			Object::ObjectScope{scope, scopeType}
		{}
		FileScope(const FileScope& src):
			Object::ObjectScope{src}
		{
			/*
			for (const auto& [key, value] : src.m_dlls)
				importDll(key);
			*/
		}
		FileScope(FileScope&&) noexcept = default;
		virtual ~FileScope() = default;
		FileScope& operator=(const FileScope& rhs)
		{
			ObjectScope::operator=(rhs);
			/*
			for (const auto &[key, value] : rhs.m_dlls)
				importDll(key);
			*/
			return *this;
		}
		FileScope &operator=(FileScope&&) noexcept = default;

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

		// std::unordered_map<std::string, std::unique_ptr<CppUtils::External::DynamicLibrary>> m_dlls;
	};
}
