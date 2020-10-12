#pragma once

#include <Parameters.hpp>
#include <Language/Language.hpp>

namespace Script
{
	using Value = Language::AST::Type::IValue;
	using Args = Language::AST::Type::Args;
	using Void = Language::AST::Type::Void;
	using Boolean = Language::AST::Type::Boolean;
	using Number = Language::AST::Type::Number;
	using String = Language::AST::Type::String;
	using FunctionSignature = Language::AST::Function::FunctionSignature;
	using Function = Language::AST::Function::Function;
	using FunctionType = Language::AST::Function::FunctionType;
	
	template<typename TargetType>
	constexpr const auto ensureType = Language::AST::Type::ensureType<TargetType>;

	class Script final
	{
	public:
		Script() = default;
		explicit Script(Settings settings):
			m_settings{std::move(settings)}
		{
			if (!m_settings.warning)
				CppUtils::Switch::disable(CppUtils::Log::Logger::WarningType);

			if (m_settings.verbose)
				CppUtils::Log::Logger::logImportant("_"s + EXECUTABLE_NAME + "_v" + EXECUTABLE_VERSION + "_/");
		}

		inline void addFunction(const FunctionSignature& functionSignature, Function function)
		{
			m_ast.addFunction(functionSignature, std::move(function));
		}

	private:
		[[nodiscard]] bool parse(std::string code)
		{
			if (m_settings.verbose)
				CppUtils::Log::Logger::logImportant("Parser:");
			auto chronoLogger = CppUtils::Log::ChronoLogger{"Parsing", m_settings.chrono};
			try
			{
				m_ast.parse(std::move(code), m_settings.verbose);
			}
			catch (const std::exception& error)
			{
				CppUtils::Log::Logger::logError("!Parsing error:\n"s + error.what());
				chronoLogger.stop();
				return false;
			}
			chronoLogger.stop();

			if (m_settings.verbose)
			{
				CppUtils::Log::Logger::logSuccess("Global namespaces: "s + std::to_string(m_ast.getNamespaces().size()));
				for (const auto& [namespaceId, namespaceScope] : m_ast.getNamespaces())
					CppUtils::Log::Logger::logInformation("- "s + namespaceId.name.data() + "{}");
				
				CppUtils::Log::Logger::logSuccess("Global classes: "s + std::to_string(m_ast.getClasses().size()));
				for (const auto& [prototypeName, prototype] : m_ast.getClasses())
					CppUtils::Log::Logger::logInformation("- "s + prototypeName + "{}");
				
				CppUtils::Log::Logger::logSuccess("Global functions: "s + std::to_string(m_ast.getFunctions().size()));
				for (const auto& [functionSignature, function] : m_ast.getFunctions())
					CppUtils::Log::Logger::logInformation("- "s + functionSignature.printable);
			}

			return true;
		}

		std::unique_ptr<Value> execute()
		{
			if (m_settings.verbose)
				CppUtils::Log::Logger::logImportant("Execution:");
			auto chronoLogger = CppUtils::Log::ChronoLogger{"Execution", m_settings.chrono};
			try
			{
				auto result = m_ast.interpret();
				chronoLogger.stop();
				return result;
			}
			catch (const std::exception& error)
			{
				CppUtils::Log::Logger::logError("!Runtime error:\n"s + error.what());
			}
			chronoLogger.stop();
			return std::make_unique<Number>(-1);
		}

	public:
		std::unique_ptr<Value> executeCode(std::string code)
		{
			if (!parse(std::move(code)))
				return std::make_unique<Number>(-1);
			return execute();
		}
		
		std::unique_ptr<Value> executeFile(const std::filesystem::path& filePath)
		{
			if (m_settings.verbose)
				CppUtils::Log::Logger::logInformation("Execute file: " + filePath.string());
			return executeCode(CppUtils::FileSystem::File::String::read(filePath));
		}

	private:
		Settings m_settings;
		Language::ASTRoot m_ast;
	};
}
