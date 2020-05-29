#include <Language/Instruction/FunctionCall.hpp>

#include <Language/Instruction/Operator.hpp>

namespace Language::Instruction
{
	std::unique_ptr<AST::Instruction> FunctionCall::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;
		
		auto functionName = parsingInformations.nextWord();
		if (functionName.empty())
			return nullptr;
		pos += functionName.length();
		parsingInformations.skipSpaces();

		if (parsingInformations.currentChar() != '(')
			return nullptr;
		++pos;

		auto functionCall = std::make_unique<FunctionCall>(std::move(functionName), &scope);
		auto functionCallParsingInformations = Parser::ParsingInformations{*functionCall, *functionCall, src, pos};
		CppUtils::Logger::logInformation(functionCall->getName().data() + "("s, false);

		parsingInformations.skipSpaces();
		while (parsingInformations.currentChar() != ',' && parsingInformations.currentChar() != ')')
		{
			functionCall->addInstruction(Operator::parseOperation(functionCallParsingInformations));
			parsingInformations.skipSpaces();
			if (parsingInformations.currentChar() == ',')
			{
				CppUtils::Logger::logInformation(", ", false);
				++pos;
			}
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
		const auto& functionScope = dynamic_cast<const AST::Scope::FunctionScope&>(getScope().findScope(AST::Scope::FunctionScopeType));
		return functionScope.getFunction(getName())(arguments);
	}

	std::unique_ptr<AST::Scope::Type::Value> FunctionCall::execute(AST::Scope::Type::Object* object) const
	{
		auto arguments = AST::Scope::Type::Args{};

		for (const auto& argument : m_instructions)
			arguments.emplace_back(dynamic_cast<AST::Instruction&>(*argument).interpret());
		return object->getFunction(getName())(arguments);
	}
}
