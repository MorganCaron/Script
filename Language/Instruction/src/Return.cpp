#include <Language/Instruction/Return.hpp>

#include <Language/Instruction/Operator.hpp>

namespace Language::Instruction
{
	std::unique_ptr<AST::Instruction> Return::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		auto word = parsingInformations.nextWord();
		if (word != keyword)
			return std::unique_ptr<Instruction>{nullptr};
		pos += word.length();
		parsingInformations.skipSpaces();

		CppUtils::Logger::logInformation(std::string{keyword} + " ", false);
		parsingInformations.skipSpaces();
		auto returnStatement = std::make_unique<Return>();
		returnStatement->addInstruction(Operator::parseOperation(parsingInformations));
		return returnStatement;
	}

	std::unique_ptr<AST::Scope::Type::Value> Return::interpret()
	{
		auto value = m_instructions.at(0)->interpret();
		auto stream = std::stringstream{};
		value->print(stream);
		CppUtils::Logger::logInformation(std::string{keyword} + " " + stream.str());
		return value;
	}
}
