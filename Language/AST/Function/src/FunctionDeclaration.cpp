#include <Language/AST/Function/FunctionDeclaration.hpp>

#include <Language/AST/Type/Number.hpp>
#include <Language/AST/Function/FunctionScope.hpp>

namespace Language::AST::Function
{
	FunctionDeclaration::FunctionDeclaration(std::string name, Scope::BaseScope* scope):
		CppUtils::Type::Named{std::move(name)},
		Core::Instruction{Type},
		Variable::VariableScope{scope},
		m_returnType{Type::VoidType}
	{}

	std::unique_ptr<ITFunction<std::unique_ptr<Type::IValue>(const Type::Args&)>> FunctionDeclaration::cloneFunction() const
	{
		return std::make_unique<FunctionDeclaration>(*this);
	}

	void FunctionDeclaration::addArgument(Variable::VariableSignature variableSignature)
	{
		addVariableSignature(variableSignature);
		m_arguments.emplace_back(std::move(variableSignature));
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
		const auto nbArguments = m_arguments.size();
		if (nbPassedArgument > nbArguments)
			throw std::runtime_error{"Le nombre d argument passes est superieur au nombre d arguments de la fonction."};
		for (auto i = std::size_t{0}; i < nbArguments; ++i)
		{
			const auto& argumentName = m_arguments[i].name;
			auto value = arguments[i]->cloneValue();
			variableScope.setVariable(argumentName, std::move(value));
		}
		return instruction.interpret();
	}

	void FunctionDeclaration::indexe()
	{
		auto& functionScope = dynamic_cast<FunctionScope&>(getScope().findScope(FunctionScopeType));
		auto argumentTypes = std::vector<CppUtils::Type::TypeId>{};
		std::transform(m_arguments.begin(), m_arguments.end(), std::back_inserter(argumentTypes), [](const auto& variableSignature) {
			return variableSignature.type;
		});
		const auto functionSignature = FunctionSignature{getName().data(), argumentTypes};
		functionScope.addFunction(functionSignature, std::make_unique<FunctionDeclaration>(*this));
		CppUtils::Log::Logger::logInformation("Declare "s + Keyword.data() + " " + functionSignature.printable);
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
