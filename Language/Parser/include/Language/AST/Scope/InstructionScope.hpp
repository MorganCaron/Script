#pragma once

#include <Language/AST/Scope/FileScope.hpp>
#include <Language/Parser/Parser.hpp>

namespace Language::AST::Scope
{
	constexpr static const ScopeType InstructionScopeType = 5;

	class InstructionScope: public FileScope
	{
	public:
		InstructionScope(BaseScope* scope = nullptr, ScopeType scopeType = InstructionScopeType):
			FileScope{scope, scopeType}
		{}
		InstructionScope(const InstructionScope&) = default;
		InstructionScope(InstructionScope&&) noexcept = default;
		virtual ~InstructionScope() = default;
		InstructionScope& operator=(const InstructionScope&) = default;
		InstructionScope &operator=(InstructionScope&&) noexcept = default;

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

		inline const std::unordered_map<std::string, Parser::InstructionParser>& getInstructions() const
		{
			return m_instructionParsers;
		}
		
	private:
		std::unordered_map<std::string, Parser::InstructionParser> m_instructionParsers;
	};
}
