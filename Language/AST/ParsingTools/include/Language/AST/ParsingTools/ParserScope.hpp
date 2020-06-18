#pragma once

#include <unordered_map>

#include <Language/AST/File/FileScope.hpp>
#include <Language/AST/ParsingTools/Cursor.hpp>

namespace Language::AST::ParsingTools
{
	constexpr static const Scope::ScopeType ParserScopeType = 5;

	class ParserScope: public File::FileScope
	{
	public:
		ParserScope(BaseScope* scope = nullptr, Scope::ScopeType scopeType = ParserScopeType):
			FileScope{scope, scopeType}
		{}
		ParserScope(const ParserScope&) = default;
		ParserScope(ParserScope&&) noexcept = default;
		virtual ~ParserScope() = default;
		ParserScope& operator=(const ParserScope&) = default;
		ParserScope &operator=(ParserScope&&) noexcept = default;

		inline bool instructionParserExists(const std::string& name) const noexcept
		{
			return (m_instructionParsers.find(name) != m_instructionParsers.end());
		}
		inline void addInstructionParser(const std::string& name, InstructionParser instructionParser)
		{
			m_instructionParsers[name] = std::move(instructionParser);
		}
		inline void addInstructionParsers(const std::unordered_map<std::string, InstructionParser>& instructionParsers)
		{
			m_instructionParsers.insert(instructionParsers.begin(), instructionParsers.end());
		}
		inline void removeInstructionParser(const std::string& name)
		{
			m_instructionParsers.erase(name);
		}
		inline const std::unordered_map<std::string, InstructionParser>& getInstructionParsers() const
		{
			return m_instructionParsers;
		}

		inline bool ValueParserExists(const std::string& name) const noexcept
		{
			return (m_valueParsers.find(name) != m_valueParsers.end());
		}
		inline void addValueParser(const std::string& name, ValueParser valueParser)
		{
			m_valueParsers[name] = std::move(valueParser);
		}
		inline void addValueParsers(const std::unordered_map<std::string, ValueParser>& valueParsers)
		{
			m_valueParsers.insert(valueParsers.begin(), valueParsers.end());
		}
		inline void removeValueParser(const std::string& name)
		{
			m_valueParsers.erase(name);
		}
		inline const std::unordered_map<std::string, ValueParser>& getValueParsers() const
		{
			return m_valueParsers;
		}

		inline bool OperatorParserExists(const std::string& name) const noexcept
		{
			return (m_operatorParsers.find(name) != m_operatorParsers.end());
		}
		inline void addOperatorParser(const std::string& name, OperatorParser operatorParser)
		{
			m_operatorParsers[name] = std::move(operatorParser);
		}
		inline void addOperatorParsers(const std::unordered_map<std::string, OperatorParser>& operatorParsers)
		{
			m_operatorParsers.insert(operatorParsers.begin(), operatorParsers.end());
		}
		inline void removeOperatorParser(const std::string& name)
		{
			m_operatorParsers.erase(name);
		}
		inline const std::unordered_map<std::string, OperatorParser>& getOperatorParsers() const
		{
			return m_operatorParsers;
		}
		
	private:
		std::unordered_map<std::string, InstructionParser> m_instructionParsers;
		std::unordered_map<std::string, ValueParser> m_valueParsers;
		std::unordered_map<std::string, OperatorParser> m_operatorParsers;
	};
}
