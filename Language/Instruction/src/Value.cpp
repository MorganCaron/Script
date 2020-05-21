#include <Language/Instruction/Value.hpp>

#include <Language/Parser/Number.hpp>
#include <Language/Parser/String.hpp>

namespace Language::Instruction
{
	Value::Value(const Value& src):
		AST::Instruction{src},
		AST::Scope::NormalScope{src}
	{
		setValue(src.getValue());
	}

	Value& Value::operator=(const Value& rhs)
	{
		AST::Instruction::operator=(rhs);
		AST::Scope::NormalScope::operator=(rhs);
		setValue(rhs.getValue());
		return *this;
	}
	
	void Value::setValue(std::unique_ptr<AST::Scope::Type::Value>&& value)
	{
		m_value = std::move(value);
	}

	std::unique_ptr<AST::Scope::Type::Value> Value::getValue() const
	{
		return m_value->cloneValue();
	}

	std::unique_ptr<Value> Value::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;
		auto value = std::unique_ptr<AST::Scope::Type::Value>{nullptr};

		if ((value = Parser::parseString(parsingInformations)) == nullptr)
			if ((value = Parser::parseNumber(parsingInformations)) == nullptr)
				return nullptr;
		return std::make_unique<Value>(std::move(value), &scope);
	}

	std::unique_ptr<AST::Scope::Type::Value> Value::interpret()
	{
		return m_value->cloneValue();
	}
}
