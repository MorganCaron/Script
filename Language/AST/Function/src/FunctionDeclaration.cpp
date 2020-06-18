#include <Language/AST/Function/FunctionDeclaration.hpp>

#include <Language/AST/Type/Number.hpp>
#include <Language/AST/Function/FunctionScope.hpp>

namespace Language::AST::Function
{
	FunctionDeclaration::FunctionDeclaration(std::string name, Scope::BaseScope* scope):
		CppUtils::Type::Named{std::move(name)},
		Core::Instruction{std::string{Type}},
		Variable::VariableScope{scope}
	{}

	std::unique_ptr<Type::ITFunction<std::unique_ptr<Type::IValue>(const Type::Args&)>> FunctionDeclaration::cloneFunction() const
	{
		return std::make_unique<FunctionDeclaration>(*this);
	}

	void FunctionDeclaration::addArgument(std::string name, Variable::VariableScope::VariableSignature&& signature)
	{
		addVariableSignature(name, std::move(signature));
		m_argumentNames.emplace_back(std::move(name));
	}

	std::unique_ptr<Type::IValue> FunctionDeclaration::operator()(const Type::Args& arguments)
	{
		if (m_instructions.empty())
			throw std::runtime_error{"La fonction ne contient aucune instruction."};
		auto& instruction = *m_instructions[0];
		auto& scope = dynamic_cast<Scope::NormalScope&>(instruction);
		auto& variableScope = dynamic_cast<Variable::VariableScope&>(scope.findScope(Variable::VariableScopeType));
		variableScope.resetVariables();
		const auto nbPassedArgument = arguments.size();
		const auto nbArguments = m_argumentNames.size();
		if (nbPassedArgument > nbArguments)
			throw std::runtime_error{"Le nombre d argument passes est superieur au nombre d arguments de la fonction."};
		for (auto i = std::size_t{0}; i < nbArguments; ++i)
		{
			const auto& argumentName = m_argumentNames[i];
			auto value = arguments[i]->cloneValue();
			variableScope.setVariable(argumentName, std::move(value));
		}
		return instruction.interpret();
	}

	void FunctionDeclaration::indexe()
	{
		CppUtils::Logger::logInformation("Declare "s + Keyword.data() + " " + getName().data() + "(", false);
		auto& functionScope = dynamic_cast<Function::FunctionScope&>(getScope().findScope(Function::FunctionScopeType));
		functionScope.addFunction(getName(), std::make_unique<FunctionDeclaration>(*this));
		CppUtils::Logger::logInformation(")");
	}

	std::unique_ptr<Type::IValue> FunctionDeclaration::interpret()
	{
		return std::make_unique<Type::Number>(0);
	}

	std::ostream& operator<<(std::ostream& os, const FunctionDeclaration& functionDeclaration)
	{
		os << "Function declaration: " << functionDeclaration.getName();
		return os;
	}
}
