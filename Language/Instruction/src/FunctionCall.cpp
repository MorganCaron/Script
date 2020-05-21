#include <Language/Instruction/FunctionCall.hpp>

#include <Language/Instruction/Operator.hpp>

namespace Language::Instruction
{
	std::unique_ptr<AST::Instruction> FunctionCall::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;
		
		auto word = parsingInformations.nextWord();
		if (word.empty())
			return nullptr;
		pos += word.length();
		parsingInformations.skipSpaces();

		if (parsingInformations.currentChar() != '(')
			return nullptr;
		++pos;

		auto functionCall = std::make_unique<FunctionCall>(std::move(word), &scope);
		auto functionCallParsingInformations = Parser::ParsingInformations{*functionCall, *functionCall, src, pos};
		CppUtils::Logger::logInformation(functionCall->getName().data() + "("s, false);

		parsingInformations.skipSpaces();
		while (parsingInformations.currentChar() != ',' && parsingInformations.currentChar() != ')')
		{
			functionCall->addInstruction(Operator::parseOperation(functionCallParsingInformations));
			parsingInformations.skipSpaces();
			if (parsingInformations.currentChar() == ',')
				++pos;
		}
		if (parsingInformations.currentChar() == ')')
			++pos;
		CppUtils::Logger::logInformation(")", false);

		return functionCall;
	}

	std::unique_ptr<AST::Scope::Type::Value> FunctionCall::interpret()
	{
		auto arguments = AST::Scope::Type::Args{};

		for (const auto& argument : m_instructions)
			arguments.emplace_back(dynamic_cast<AST::Instruction&>(*argument).interpret());
		return dynamic_cast<AST::Scope::FunctionScope&>(getScope().findScope(AST::Scope::FunctionScopeType)).getFunction(getName())(arguments);
	}

	std::unique_ptr<AST::Scope::Type::Value> FunctionCall::execute(AST::Scope::Type::Object* object) const
	{
		auto arguments = AST::Scope::Type::Args{};

		for (const auto& argument : m_instructions)
			arguments.emplace_back(dynamic_cast<AST::Instruction&>(*argument).interpret());
		return object->getFunction(getName())(arguments);
	}
}
