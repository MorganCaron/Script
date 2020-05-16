#pragma once

#include <Language/AST.hpp>

namespace Script
{
	using Value = Language::Scope::Type::Value;
	using Args = Language::Scope::Type::Args;
	using Number = Language::Scope::Type::Number;
	using String = Language::Scope::Type::String;
	using Function = Language::Scope::FunctionType;
	using ExternalFunction = Language::Scope::Type::Function<std::unique_ptr<Value>(const Args&)>;

	class Script final
	{
	public:
		Script() = default;

		inline void addFunction(std::string name, std::unique_ptr<Function>&& function)
		{
			m_ast.addFunction(std::move(name), std::move(function));	
		}

	private:
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

		std::unique_ptr<Value> execute()
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
			return std::make_unique<Number>(0);
		}

	public:
		std::unique_ptr<Value> executeCode(std::string code)
		{
			parse(std::move(code));
			interpret();
			return execute();
		}
		
		std::unique_ptr<Value> executeFile(const std::filesystem::path& filePath)
		{
			CppUtils::Logger::logInformation("Execute file: " + filePath.string());
			return executeCode(CppUtils::FileSystem::readString(filePath));
		}

	private:
		Language::AST m_ast;
	};
}
