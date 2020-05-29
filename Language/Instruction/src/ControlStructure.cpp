#include <Language/Instruction/ControlStructure.hpp>

#include <Language/Instruction/Operator.hpp>
#include <Language/AST/Scope/Type/Number.hpp>

namespace Language::Instruction
{
	ControlStructure::ControlStructure(std::string name, AST::Scope::BaseScope* scope):
		CppUtils::Type::Named{std::move(name)},
		AST::Instruction{std::string{Type}},
		AST::Scope::NormalScope{scope}
	{
		if (getName() == "if")
			m_sort = eControlStructureSort::IF;
		else if (getName() == "while")
			m_sort = eControlStructureSort::WHILE;
	}

	std::unique_ptr<AST::Instruction> ControlStructure::parse(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;

		auto keyword = parsingInformations.nextWord();
		static const auto controlStructureWords = std::vector<std::string>{"if", "then", "while", "else", "do", "switch", "case", "repeat", "break", "for"};
		if (std::find(controlStructureWords.begin(), controlStructureWords.end(), keyword) == controlStructureWords.end())
			return nullptr;
		pos += keyword.length();
		parsingInformations.skipSpaces();

		auto controlStructure = std::make_unique<ControlStructure>(keyword, &scope);
		auto controlStructureParsingInformations = Parser::ParsingInformations{*controlStructure, *controlStructure, src, pos};

		CppUtils::Logger::logInformation(controlStructure->getName().data() + " ("s, false);
		controlStructure->addInstruction(Operator::parseOperation(controlStructureParsingInformations));
		CppUtils::Logger::logInformation(") ", false);

		parsingInformations.skipSpaces();
		if (parsingInformations.currentChar() == ':')
			++pos;
		
		if (Parser::parseInstruction(controlStructureParsingInformations) == nullptr)
			throw std::runtime_error{"La condition doit etre suivie d une instruction."};
		
		return controlStructure;
	}

	std::unique_ptr<AST::Scope::Type::Value> ControlStructure::interpret()
	{
		bool condition, loop = true;
		std::unique_ptr<AST::Scope::Type::Value> value;

		while (loop)
		{
			value = m_instructions[0]->interpret();
			if (value->getType() == AST::Scope::Type::Number::Type)
				condition = (*value != AST::Scope::Type::Number{});
			else
				condition = false;
			if (condition)
				m_instructions[1]->interpret();
			if (m_sort == eControlStructureSort::WHILE)
				loop = condition;
			else if (m_sort == eControlStructureSort::IF)
				loop = false;
		}
		return 0;
	}
}
