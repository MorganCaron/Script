#include "Language/ControlStructure.hpp"

#include <Language/Scope/Type/Number.hpp>
#include "Language/AST.hpp"
#include "Language/Operator.hpp"

namespace Language
{
	ControlStructure::ControlStructure(std::string name, Scope::BaseScope* scope):
		CppUtils::Type::Named{std::move(name)},
		Instruction{InstructionType::CONTROLSTRUCTURE},
		NormalScope{scope}
	{
		if (getName() == "if")
			m_sort = eControlStructureSort::IF;
		else if (getName() == "while")
			m_sort = eControlStructureSort::WHILE;
	}

	void ControlStructure::parse(ParsingInformations& parsingInformations)
	{
		CppUtils::Logger::logInformation(getName().data() + " ("s, false);
		addInstruction(Operator::parseOperation(*this, getScope(), parsingInformations));
		CppUtils::Logger::logInformation(") ", false);
		if (!AST::parseInstruction(*this, getScope(), parsingInformations))
			throw std::runtime_error("La condition doit etre suivie d une instruction.");
	}

	std::unique_ptr<Scope::Type::Value> ControlStructure::interpret()
	{
		bool condition, loop = true;
		std::unique_ptr<Scope::Type::Value> value;

		while (loop)
		{
			value = m_instructions[0]->interpret();
			if (value->getType() == Scope::Type::NumberType)
				condition = (*value != Scope::Type::Number{});
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
