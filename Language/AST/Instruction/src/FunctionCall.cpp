#include <Language/AST/Instruction/FunctionCall.hpp>

#include <Language/AST/Instruction/Operator.hpp>

namespace Language::AST::Instruction
{
	std::unique_ptr<Type::IValue> FunctionCall::interpret()
	{
		auto arguments = Type::Args{};

		for (const auto& argument : m_instructions)
			arguments.emplace_back(dynamic_cast<Core::Instruction&>(*argument).interpret());
		const auto& functionScope = dynamic_cast<const Function::FunctionScope&>(getScope().findScope(Function::FunctionScopeType));
		return functionScope.getFunction(getName())(arguments);
	}

	std::unique_ptr<Type::IValue> FunctionCall::execute(Object::Instance* object) const
	{
		auto arguments = Type::Args{};

		for (const auto& argument : m_instructions)
			arguments.emplace_back(dynamic_cast<Core::Instruction&>(*argument).interpret());
		return object->getFunction(getName())(arguments);
	}
}
