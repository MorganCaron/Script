#include <Language/AST/Instruction/ControlStructure.hpp>

#include <Language/AST/Type/Boolean.hpp>

namespace Language::AST::Instruction
{
	ControlStructure::ControlStructure(std::string name, Scope::BaseScope* scope):
		CppUtils::Type::Named{std::move(name)},
		Core::Instruction{Type},
		Scope::NormalScope{scope}
	{
		if (getName() == "if")
			m_sort = eControlStructureSort::IF;
		else if (getName() == "while")
			m_sort = eControlStructureSort::WHILE;
	}

	std::unique_ptr<Type::IValue> ControlStructure::interpret()
	{
		bool condition, loop = true;

		while (loop)
		{
			const auto value = m_instructions[0]->interpret();
			if (!value->isType(Type::Boolean::TypeId))
				throw std::runtime_error{"La structure de controle attend une valeur numerique."};
			condition = (dynamic_cast<Type::Boolean*>(value.get())->getValue() == false);
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
