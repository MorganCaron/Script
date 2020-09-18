#include <Language/AST/Instruction/FunctionCall.hpp>

#include <Language/AST/Instruction/Operator.hpp>
#include <Language/AST/Function/FunctionScope.hpp>

namespace Language::AST::Instruction
{
	std::unique_ptr<Type::IValue> FunctionCall::interpret()
	{
		auto arguments = Type::Args{};
		std::transform(m_instructions.begin(), m_instructions.end(), std::back_inserter(arguments), [](const auto& argument) {
			return argument->interpret();
		});
		const auto& functionScope = dynamic_cast<const Function::FunctionScope&>(getScope().findScope(Function::FunctionScopeType));
		const auto functionSignature = Function::FunctionSignature{getName().data(), m_argumentTypes};
		auto& function = functionScope.getFunction(functionSignature);
		return function(arguments);
	}

	[[nodiscard]] const CppUtils::Type::TypeId& FunctionCall::getReturnType() const
	{
		const auto& functionScope = dynamic_cast<const Function::FunctionScope&>(getScope().findScope(Function::FunctionScopeType));
		const auto functionSignature = Function::FunctionSignature{getName().data(), m_argumentTypes};
		auto& function = functionScope.getFunction(functionSignature);
		return function.getReturnType();
	}

	std::unique_ptr<Type::IValue> FunctionCall::execute(Object::Instance* object) const
	{
		auto arguments = Type::Args{};
		std::transform(m_instructions.begin(), m_instructions.end(), std::back_inserter(arguments), [](const auto& argument) {
			return argument->interpret();
		});
		const auto functionSignature = Function::FunctionSignature{getName().data(), m_argumentTypes};
		auto& function = object->getFunction(functionSignature);
		return function(arguments);
	}
}
