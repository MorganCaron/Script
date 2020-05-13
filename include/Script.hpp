#pragma once

#include <Language/AST.hpp>

namespace Script
{
	class Script final
	{
	public:
		Script() = default;

		inline void addFunction(std::string name, std::unique_ptr<Language::Scope::FunctionType>&& function)
		{
			m_ast.addFunction(std::move(name), std::move(function));	
		}

		void parse(std::string code)
		{
			try
			{
				m_ast.parse(std::move(code));
			}
			catch (const std::exception& error)
			{
				CppUtils::Logger::logError("!Parsing error: "s + error.what());
			}
		}

		void interpret()
		{
			try
			{
				m_ast.interpret();
				CppUtils::Logger::logInformation(">Functions: "s + std::to_string(m_ast.getFunctions().size()));
				for (const auto& function : m_ast.getFunctions())
					CppUtils::Logger::logInformation("- "s + function.first + "()");
			}
			catch (const std::exception& error)
			{
				CppUtils::Logger::logError("!Interpretation error: "s + error.what());
			}
		}

		std::unique_ptr<Language::Scope::Type::Value> execute()
		{
			CppUtils::Logger::logInformation("#- EXECUTION_/");
			try
			{
				if (!m_ast.functionExists("main"))
					throw std::runtime_error{"Fonction main() requise."};
				CppUtils::Logger::logInformation(">main()");
				return m_ast.getFunction("main")({});
			}
			catch (const std::exception& error)
			{
				CppUtils::Logger::logError("!Runtime error: "s + error.what());
			}
			return std::make_unique<Language::Scope::Type::Number>(0);
		}

		std::unique_ptr<Language::Scope::Type::Value> executeCode(std::string code)
		{
			parse(std::move(code));
			interpret();
			return execute();
		}
		
		std::unique_ptr<Language::Scope::Type::Value> executeFile(const std::filesystem::path& filePath)
		{
			CppUtils::Logger::logInformation("Execute file: " + filePath.string());
			return executeCode(CppUtils::FileSystem::readString(filePath));
		}

	private:
		Language::AST m_ast;
	};
}
