#include "Language/Operator.hpp"

#include "Language/AST.hpp"
#include "Language/Variable.hpp"
#include "Language/Value.hpp"
#include "Language/FunctionCall.hpp"

namespace Language
{
	Operator::Operator(std::string name, Scope::BaseScope* scope):
		CppUtils::Type::Named{std::move(name)},
		Instruction{InstructionType::OPERATOR},
		NormalScope{scope}
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
			throw std::runtime_error("Operateur "s + std::string{getName()} + " inconnu.");
		m_priority = operators.at(getName());
	}

	std::unique_ptr<Scope::Type::Value> Operator::interpret()
	{
		std::unique_ptr<Scope::Type::Value> result;
		auto& operand0 = m_instructions[0];
		auto& operand1 = m_instructions[1];
		auto value0 = operand0->interpret();

		if (getName() == "=" && operand0->getInstructionType() == InstructionType::VARIABLE && !dynamic_cast<const Scope::VariableScope&>(getScope().findScope(Scope::VariableScopeType)).variableExists(dynamic_cast<Variable*>(operand0.get())->getName()))
			dynamic_cast<Variable*>(operand0.get())->setValue(std::make_unique<Scope::Type::Number>());
		if (getName() == ".")
		{
			if (value0->getType() != Scope::Type::Object::type)
				throw std::runtime_error{"L element avant le point doit etre un objet."};
			auto object = dynamic_cast<Scope::Type::Object*>(value0.get());
			if (object == nullptr)
				throw std::runtime_error{"Cet objet ne peut pas etre utilise ici car il a ete supprime."};
			if (operand1->getInstructionType() != InstructionType::FUNCTIONCALL)
				throw std::runtime_error{"L element apres le point d un objet doit etre une fonction membre."};
			result = dynamic_cast<FunctionCall*>(operand1.get())->execute(object);
		}
		else
		{
			result = doOp(value0, getName(), operand1->interpret());
		}
		if (getName() == "=" || getName() == "+=" || getName() == "-=" || getName() == "*=" || getName() == "/=")
			dynamic_cast<Variable*>(operand0.get())->setValue(result->cloneValue());
		return result;
	}

	std::unique_ptr<Scope::Type::Value> Operator::doOp(const std::unique_ptr<Scope::Type::Value>& val1, std::string_view op, const std::unique_ptr<Scope::Type::Value>& val2)
	{
		static const auto operations = std::unordered_map<std::string, std::function<std::unique_ptr<Scope::Type::Value>(const Scope::Type::Value&, const Scope::Type::Value&)>>{
			{ "=", []([[maybe_unused]]const auto& val1, const auto& val2) -> std::unique_ptr<Scope::Type::Value> { return val2.cloneValue(); } },
			{ "+", [](const auto& val1, const auto& val2) -> std::unique_ptr<Scope::Type::Value> { return std::unique_ptr<Scope::Type::Value>(val1 + val2); } },
			{ "-", [](const auto& val1, const auto& val2) -> std::unique_ptr<Scope::Type::Value> { return std::unique_ptr<Scope::Type::Value>(val1 - val2); } },
			{ "*", [](const auto& val1, const auto& val2) -> std::unique_ptr<Scope::Type::Value> { return std::unique_ptr<Scope::Type::Value>(val1 * val2); } },
			{ "/", [](const auto& val1, const auto& val2) -> std::unique_ptr<Scope::Type::Value> { return std::unique_ptr<Scope::Type::Value>(val1 / val2); } },
			{ "%", [](const auto& val1, const auto& val2) -> std::unique_ptr<Scope::Type::Value> { return std::unique_ptr<Scope::Type::Value>(val1 % val2); } }
		};
		if (operations.find(op.data()) == operations.end())
			throw std::runtime_error{"Operateur " + std::string{op} + " inconnu."};
		return operations.at(op.data())(*val1, *val2);
	}

	std::unique_ptr<Instruction> Operator::parseOperand(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;
		std::unique_ptr<Instruction> instruction, operand;

		AST::parseSpace(parsingInformations);
		if (code.at(pos) == '+' || code.at(pos) == '-' || code.at(pos) == '!')
		{
			auto op = std::make_unique<Operator>(code.substr(pos++, 1), &scope);
			// op->moveInstruction(std::move(std::make_unique<Value>(std::make_unique<Number>(0), scope)));
			operand = parseOperand(*op.get(), scope, parsingInformations);
			if (operand)
				op->addInstruction(std::move(operand));
			return op;
		}
		AST::parseSpace(parsingInformations);
		instruction = Value::parse(container, scope, parsingInformations);
		if (instruction != nullptr)
			return instruction;
		auto word = parsingInformations.nextWord();
		if (!word.empty())
		{
			pos += word.size();
			instruction = FunctionCall::parse(container, scope, parsingInformations, word);
			if (instruction)
				return instruction;
			return Variable::parse(container, scope, parsingInformations, word);
		}
		else if (code.at(pos) == '(')
		{
			++pos;
			instruction = parseOperation(container, scope, parsingInformations);
			AST::parseSpace(parsingInformations);
			if (code.at(pos++) != ')')
				throw std::runtime_error("Une parenthese n est pas fermee.");
			return instruction;
		}
		else
			throw std::runtime_error("Un operande est attendu.");
		return nullptr;
	}

	std::unique_ptr<Operator> Operator::parseOperator([[maybe_unused]] InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations)
	{
		auto& [code, pos] = parsingInformations;
		auto expression = std::string{};

		AST::parseSpace(parsingInformations);
		while (std::string(OperatorChar).find(code.at(pos)) != std::string::npos)
			expression += code.at(pos++);
		if (expression.empty())
			return nullptr;
		CppUtils::Logger::logInformation(" "s + expression + ' ', false);
		return std::make_unique<Operator>(expression, &scope);
	}

	std::unique_ptr<Instruction> Operator::parseOperation(InstructionContainer& container, Scope::BaseScope& scope, ParsingInformations& parsingInformations, std::unique_ptr<Instruction>&& lhs, std::unique_ptr<Operator>&& nextOperator)
	{
		std::unique_ptr<Instruction> rhs = nullptr;

		if (lhs == nullptr)
			lhs = parseOperand(container, scope, parsingInformations);
		if (nextOperator == nullptr)
			nextOperator = parseOperator(container, scope, parsingInformations);
		while (nextOperator)
		{
			auto currentOperator = std::move(nextOperator);
			currentOperator->addInstruction(std::move(lhs));
			rhs = parseOperand(*currentOperator.get(), scope, parsingInformations);
			nextOperator = parseOperator(*currentOperator.get(), scope, parsingInformations);
			if (!nextOperator || currentOperator->getPriority() > nextOperator->getPriority())
				currentOperator->addInstruction(std::move(rhs));
			else
			{
				currentOperator->addInstruction(parseOperation(*currentOperator.get(), scope, parsingInformations, std::move(rhs), std::move(nextOperator)));
				return currentOperator;
			}
			lhs = std::move(currentOperator);
		}
		return std::move(lhs);
	}

	std::ostream& operator<<(std::ostream& os, const Operator& op)
	{
		os << op.getName();
		return os;
	}
}
