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
				CppUtils::Logger::log(CppUtils::Logger::OutputType::Cerr, CppUtils::Logger::MessageType::Error, "!Parsing error: "s + error.what());
			}
		}

		void interpret()
		{
			try
			{
				m_ast.interpret();
				CppUtils::Logger::log(CppUtils::Logger::OutputType::Cout, CppUtils::Logger::MessageType::Information, ">Functions: "s + std::to_string(m_ast.getFunctions().size()));
				for (const auto& function : m_ast.getFunctions())
					CppUtils::Logger::log(CppUtils::Logger::OutputType::Cout, CppUtils::Logger::MessageType::Information, "- "s + function.first);
			}
			catch (const std::exception& error)
			{
				CppUtils::Logger::log(CppUtils::Logger::OutputType::Cerr, CppUtils::Logger::MessageType::Error, "!Interpretation error: "s + error.what());
			}
		}

		void execute()
		{
			try
			{
				if (m_ast.functionExists("init"))
				{
					CppUtils::Logger::log(CppUtils::Logger::OutputType::Cout, CppUtils::Logger::MessageType::Information, ">init()");
					m_ast.getFunction("init")({});
				}

				if (m_ast.functionExists("update"))
				{
					CppUtils::Logger::log(CppUtils::Logger::OutputType::Cout, CppUtils::Logger::MessageType::Information, ">update()");
					m_ast.getFunction("update")({});
				}
				
				if (m_ast.functionExists("destroy"))
				{
					CppUtils::Logger::log(CppUtils::Logger::OutputType::Cout, CppUtils::Logger::MessageType::Information, ">destroy()");
					m_ast.getFunction("destroy")({});
				}
			}
			catch (const std::exception& error)
			{
				CppUtils::Logger::log(CppUtils::Logger::OutputType::Cerr, CppUtils::Logger::MessageType::Error, "!Runtime error: "s + error.what());
			}
		}

		void executeCode(std::string code)
		{
			parse(std::move(code));
			interpret();
			execute();
		}
		
		void executeFile(const std::filesystem::path& filePath)
		{
			CppUtils::Logger::log(CppUtils::Logger::OutputType::Cout, CppUtils::Logger::MessageType::Information, "Execute file: " + filePath.string());
			executeCode(CppUtils::FileSystem::readString(filePath));
		}

	private:
		Language::AST m_ast;
	};
}
