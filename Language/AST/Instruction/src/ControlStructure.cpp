#include <Language/AST/Instruction/ControlStructure.hpp>

#include <Language/AST/Type/Boolean.hpp>

namespace Language::AST::Instruction
{
	ControlStructure::ControlStructure(std::string name, Scope::NormalScope* scope):
		CppUtils::Type::Named{std::move(name)},
		Core::InstructionContainer{Type},
		Scope::NormalScope{scope}
	{
		if (getName() == "if")
			m_sort = eControlStructureSort::IF;
		else if (getName() == "while")
			m_sort = eControlStructureSort::WHILE;
	}

	std::unique_ptr<Type::IValue> ControlStructure::interpret()
	{
		auto loop = bool{true};

		while (loop)
		{
			const auto value = m_instructions[0]->interpret();
			if (!value->isType(Type::Boolean::TypeId))
				throw std::runtime_error{"La structure de controle attend une valeur numerique."};
			const auto condition = Type::ensureType<Type::Boolean>(value)->getValue();
			if (condition)
				m_instructions[1]->interpret();
			if (m_sort == eControlStructureSort::WHILE)
				loop = condition;
			else if (m_sort == eControlStructureSort::IF)
				loop = false;
		}
		return std::make_unique<Type::Void>(nullptr);
	}
}
