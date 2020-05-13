#include "Language/FunctionCall.hpp"

#include "Language/AST.hpp"
#include "Language/Operator.hpp"

namespace Language
{
	void FunctionCall::parse(ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;

		CppUtils::Logger::logInformation(getName().data() + "("s, false);
		AST::parseSpace(parsingInformations);
		while (parsingInformations.currentChar() != ',' && parsingInformations.currentChar() != ')')
		{
			addInstruction(Operator::parseOperation(*this, getScope(), parsingInformations));
			AST::parseSpace(parsingInformations);
			if (parsingInformations.currentChar() == ',')
				++pos;
		}
		if (parsingInformations.currentChar() == ')')
			++pos;
		CppUtils::Logger::logInformation(")", false);
	}

	std::unique_ptr<Scope::Type::Value> FunctionCall::interpret()
	{
		auto arguments = Scope::Type::Args{};

		for (const auto& argument : m_instructions)
			arguments.emplace_back(dynamic_cast<Instruction&>(*argument).interpret());
		return dynamic_cast<Scope::FunctionScope&>(getScope().findScope(Scope::FunctionScopeType)).getFunction(getName())(arguments);
	}

	std::unique_ptr<Scope::Type::Value> FunctionCall::execute(Scope::Type::Object* object) const
	{
		auto arguments = Scope::Type::Args{};

		for (const auto& argument : m_instructions)
			arguments.emplace_back(dynamic_cast<Instruction&>(*argument).interpret());
		return object->getFunction(getName())(arguments);
	}

	std::unique_ptr<Instruction> FunctionCall::parse([[maybe_unused]] InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations, std::string word)
	{
		auto& [code, pos] = parsingInformations;

		AST::parseSpace(parsingInformations);
		if (parsingInformations.currentChar() == '(')
		{
			auto functionCall = std::make_unique<FunctionCall>(std::move(word), &scope);
			++pos;
			functionCall->parse(parsingInformations);
			return functionCall;
		}
		return nullptr;
	}
}
