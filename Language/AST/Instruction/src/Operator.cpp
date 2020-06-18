#include <Language/AST/Instruction/Operator.hpp>
/*
#include <Language/AST/Variable/Variable.hpp>
#include <Language/AST/Instruction/FunctionCall.hpp>
#include <Language/AST/Type/Number.hpp>

namespace Language::AST::Instruction
{
	Operator::Operator(std::string name, Scope::BaseScope* scope):
		CppUtils::Type::Named{std::move(name)},
		Core::Instruction{std::string{Type}},
		Scope::NormalScope{scope}
	{
		static const auto operators = std::unordered_map<std::string_view, eOperatorPriority>{
			{ ".", eOperatorPriority::MEMFUNC },
			{ "+", eOperatorPriority::ADDSUB },
			{ "-", eOperatorPriority::ADDSUB },
			{ "!", eOperatorPriority::ADDSUB },
			{ "*", eOperatorPriority::MULDIV },
			{ "/", eOperatorPriority::MULDIV },
			{ "%", eOperatorPriority::MULDIV },
			{ "=", eOperatorPriority::ASSIGNMENT },
			{ "+=", eOperatorPriority::ASSIGNMENT },
			{ "-=", eOperatorPriority::ASSIGNMENT },
			{ "*=", eOperatorPriority::ASSIGNMENT },
			{ "/=", eOperatorPriority::ASSIGNMENT },
			{ "&&", eOperatorPriority::BINARY },
			{ "||", eOperatorPriority::BINARY },
			{ "^^", eOperatorPriority::BINARY },
			{ "<", eOperatorPriority::BINARY },
			{ ">", eOperatorPriority::BINARY },
			{ "<=", eOperatorPriority::BINARY },
			{ ">=", eOperatorPriority::BINARY },
			{ "==", eOperatorPriority::BINARY },
			{ "!=", eOperatorPriority::BINARY }
		};
		if (operators.find(getName()) == operators.end())
			throw std::runtime_error{"Operateur "s + std::string{getName()} + " inconnu."};
		m_priority = operators.at(getName());
	}

	std::unique_ptr<Type::IValue> Operator::interpret()
	{
		if (getName() == "=" && operand0->getInstructionType() == Variable::Variable::Type && !dynamic_cast<const Variable::VariableScope&>(getScope().findScope(Variable::VariableScopeType)).variableExists(dynamic_cast<Variable::Variable*>(operand0.get())->getName()))
			dynamic_cast<Variable::Variable*>(operand0.get())->setValue(std::make_unique<Type::Number>());
		if (getName() == ".")
		{
			if (value0->getType() != Object::Instance::type)
				throw std::runtime_error{"L element avant le point doit etre un objet."};
			auto object = dynamic_cast<Object::Instance*>(value0.get());
			if (object == nullptr)
				throw std::runtime_error{"Cet objet ne peut pas etre utilise ici car il a ete supprime."};
			if (operand1->getInstructionType() != FunctionCall::type)
				throw std::runtime_error{"L element apres le point d un objet doit etre une fonction membre."};
			result = dynamic_cast<FunctionCall*>(operand1.get())->execute(object);
		}
		else
		{
			result = doOp(value0, getName(), operand1->interpret());
		}
		if (getName() == "=" || getName() == "+=" || getName() == "-=" || getName() == "*=" || getName() == "/=")
			dynamic_cast<Variable::Variable*>(operand0.get())->setValue(result->cloneValue());
		
		result = std::move(value0);
		return result;
	}

	std::unique_ptr<Type::IValue> Operator::doOp(const std::unique_ptr<Type::IValue>& val1, std::string_view op, const std::unique_ptr<Type::IValue>& val2)
	{
		static const auto operations = std::unordered_map<std::string, std::function<std::unique_ptr<Type::IValue>(const Type::Value&, const Type::Value&)>>{
			{ "=", []([[maybe_unused]] const auto& val1, const auto& val2) -> std::unique_ptr<Type::IValue> { return val2.cloneValue(); } },
			{ "+", [](const auto& val1, const auto& val2) -> std::unique_ptr<Type::IValue> { return std::unique_ptr<Type::IValue>(val1 + val2); } },
			{ "-", [](const auto& val1, const auto& val2) -> std::unique_ptr<Type::IValue> { return std::unique_ptr<Type::IValue>(val1 - val2); } },
			{ "*", [](const auto& val1, const auto& val2) -> std::unique_ptr<Type::IValue> { return std::unique_ptr<Type::IValue>(val1 * val2); } },
			{ "/", [](const auto& val1, const auto& val2) -> std::unique_ptr<Type::IValue> { return std::unique_ptr<Type::IValue>(val1 / val2); } },
			{ "%", [](const auto& val1, const auto& val2) -> std::unique_ptr<Type::IValue> { return std::unique_ptr<Type::IValue>(val1 % val2); } }
		};
		if (operations.find(op.data()) == operations.end())
			throw std::runtime_error{"Operateur " + std::string{op} + " inconnu."};
		return operations.at(op.data())(*val1, *val2);
	}

	std::ostream& operator<<(std::ostream& os, const Operator& op)
	{
		os << op.getName();
		return os;
	}
}
*/
