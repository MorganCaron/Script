#pragma once

#include <Language/AST/Scope/FileScope.hpp>
#include <Language/Parser/Parser.hpp>

namespace Language::AST::Scope
{
	constexpr static const ScopeType LanguageScopeType = 5;

	class LanguageScope: public FileScope
	{
	public:
		LanguageScope(BaseScope* scope = nullptr, ScopeType scopeType = LanguageScopeType):
			FileScope{scope, scopeType}
		{}
		LanguageScope(const LanguageScope&) = default;
		LanguageScope(LanguageScope&&) noexcept = default;
		virtual ~LanguageScope() = default;
		LanguageScope& operator=(const LanguageScope&) = default;
		LanguageScope &operator=(LanguageScope&&) noexcept = default;

		inline bool instructionParserExists(const std::string& name) const noexcept
		{
			return (m_instructionParsers.find(name) != m_instructionParsers.end());
		}
		inline void addInstructionParser(const std::string& name, Parser::InstructionParser instructionParser)
		{
			m_instructionParsers[name] = std::move(instructionParser);
		}
		inline void addInstructionParsers(const std::unordered_map<std::string, Parser::InstructionParser>& instructionParsers)
		{
			m_instructionParsers.insert(instructionParsers.begin(), instructionParsers.end());
		}
		inline void removeInstructionParser(const std::string& name)
		{
			m_instructionParsers.erase(name);
		}
		inline const std::unordered_map<std::string, Parser::InstructionParser>& getInstructionParsers() const
		{
			return m_instructionParsers;
		}

		inline bool ValueParserExists(const std::string& name) const noexcept
		{
			return (m_valueParsers.find(name) != m_valueParsers.end());
		}
		inline void addValueParser(const std::string& name, Parser::ValueParser valueParser)
		{
			m_valueParsers[name] = std::move(valueParser);
		}
		inline void addValueParsers(const std::unordered_map<std::string, Parser::ValueParser>& valueParsers)
		{
			m_valueParsers.insert(valueParsers.begin(), valueParsers.end());
		}
		inline void removeValueParser(const std::string& name)
		{
			m_valueParsers.erase(name);
		}
		inline const std::unordered_map<std::string, Parser::ValueParser>& getValueParsers() const
		{
			return m_valueParsers;
		}
		
	private:
		std::unordered_map<std::string, Parser::InstructionParser> m_instructionParsers;
		std::unordered_map<std::string, Parser::ValueParser> m_valueParsers;
	};
}
