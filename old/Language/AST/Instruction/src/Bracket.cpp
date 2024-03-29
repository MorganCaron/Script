#include <Language/AST/Instruction/Bracket.hpp>

#include <Language/AST/Instruction/Return.hpp>

namespace Script::Language::AST::Instruction
{
	std::unique_ptr<Type::IValue> Bracket::interpret()
	{
		for (auto& instruction : m_instructions)
		{
			auto result = instruction->interpret();
			if (instruction->getType() == Return::Type)
				return result;
		}
		return std::make_unique<Type::Void>(nullptr);
	}
}
