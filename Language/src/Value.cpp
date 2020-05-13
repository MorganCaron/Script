#include "Language/Value.hpp"

#include "Language/AST.hpp"

namespace Language
{
	Value::Value(const Value& src):
		Instruction{src},
		NormalScope{src}
	{
		setValue(src.getValue());
	}

	Value& Value::operator=(const Value& rhs)
	{
		Instruction::operator=(rhs);
		NormalScope::operator=(rhs);
		setValue(rhs.getValue());
		return *this;
	}
	
	void Value::setValue(std::unique_ptr<Scope::Type::Value>&& value)
	{
		m_value = std::move(value);
	}

	std::unique_ptr<Scope::Type::Value> Value::getValue() const
	{
		return m_value->cloneValue();
	}

	std::unique_ptr<Scope::Type::Value> Value::interpret()
	{
		return m_value->cloneValue();
	}

	std::unique_ptr<Value> Value::parse(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations)
	{
		auto value = std::unique_ptr<Scope::Type::Value>(nullptr);

		if ((value = parseString(container, parsingInformations)) == nullptr)
			if ((value = parseNumber(container, parsingInformations)) == nullptr)
				return nullptr;
		return std::make_unique<Value>(std::move(value), &scope);
	}

	std::unique_ptr<Scope::Type::Number> Value::parseNumber([[maybe_unused]] InstructionContainer& container, ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;
		auto buffer = std::string{};
		auto nb = double{};

		while (std::string(NumberChar).find(parsingInformations.currentChar()) != std::string::npos)
			buffer += code.at(pos++);
		if (parsingInformations.currentChar() == '.')
			buffer += code.at(pos++);
		while (std::string(NumberChar).find(parsingInformations.currentChar()) != std::string::npos)
			buffer += code.at(pos++);
		if (!buffer.empty())
		{
			CppUtils::Logger::logInformation(buffer, false);
			std::stringstream ss(buffer.c_str());
			ss >> nb;
			return std::make_unique<Scope::Type::Number>(nb);
		}
		return nullptr;
	}

	std::unique_ptr<Scope::Type::String> Value::parseString([[maybe_unused]] InstructionContainer& container, ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;
		auto quoteChar = parsingInformations.currentChar();
		auto buffer = std::string();
		auto length = code.length();

		if (quoteChar == '"' || quoteChar == '\'')
		{
			while (++pos < length && parsingInformations.currentChar() != quoteChar)
				buffer += parsingInformations.currentChar();
			if (pos == length)
				throw std::runtime_error{std::string(quoteChar == '"' ? "Guillemet" : "Apostrophe") + " non fermes."};
			++pos;
			CppUtils::Logger::logInformation("\""s + buffer + '"', false);
			return std::make_unique<Scope::Type::String>(buffer);
		}
		return nullptr;
	}
}
