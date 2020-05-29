#include <Language/Instruction/Operator.hpp>

#include <Language/Instruction/Variable.hpp>
#include <Language/Instruction/Value.hpp>
#include <Language/Instruction/FunctionCall.hpp>

namespace Language::Instruction
{
	Operator::Operator(std::string name, AST::Scope::BaseScope* scope):
		CppUtils::Type::Named{std::move(name)},
		AST::Instruction{std::string{Type}},
		AST::Scope::NormalScope{scope}
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

	std::unique_ptr<AST::Instruction> Operator::parseOperand(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;
		auto instruction = std::unique_ptr<AST::Instruction>{nullptr};
		auto operand = std::unique_ptr<AST::Instruction>{nullptr};

		parsingInformations.skipSpaces();
		if (parsingInformations.currentChar() == '+' ||
			parsingInformations.currentChar() == '-' ||
			parsingInformations.currentChar() == '!')
		{
			auto op = std::make_unique<Operator>(src.substr(pos++, 1), &scope);
			auto operatorParsingInformations = Parser::ParsingInformations{*op, scope, src, pos};
			// op->moveInstruction(std::move(std::make_unique<Value>(std::make_unique<Number>(0), scope)));
			
			operand = parseOperand(operatorParsingInformations);
			if (operand)
				op->addInstruction(std::move(operand));
			return op;
		}
		
		instruction = Value::parse(parsingInformations);
		if (instruction != nullptr)
			return instruction;
		if (std::string{Parser::AlphaChar}.find(parsingInformations.currentChar()) != std::string::npos)
		{
			auto startPos = pos;
			if ((instruction = FunctionCall::parse(parsingInformations)) != nullptr)
				return instruction;
			pos = startPos;
			return Variable::parse(parsingInformations);
		}
		else if (src.at(pos) == '(')
		{
			++pos;
			instruction = parseOperation(parsingInformations);
			parsingInformations.skipSpaces();
			if (src.at(pos++) != ')')
				throw std::runtime_error{"Une parenthese n est pas fermee."};
			return instruction;
		}
		else
			throw std::runtime_error{"Un operande est attendu."};
		return nullptr;
	}

	std::unique_ptr<Operator> Operator::parseOperator(Parser::ParsingInformations& parsingInformations)
	{
		auto& [container, scope, src, pos] = parsingInformations;
		auto expression = std::string{};

		parsingInformations.skipSpaces();
		while (std::string(Parser::OperatorChar).find(src.at(pos)) != std::string::npos)
			expression += src.at(pos++);
		if (expression.empty())
			return nullptr;
		CppUtils::Logger::logInformation(" "s + expression + ' ', false);
		return std::make_unique<Operator>(expression, &scope);
	}

	std::unique_ptr<AST::Instruction> Operator::parseOperation(Parser::ParsingInformations& parsingInformations, std::unique_ptr<AST::Instruction>&& lhs, std::unique_ptr<Operator>&& nextOperator)
	{
		auto& [container, scope, src, pos] = parsingInformations;
		std::unique_ptr<AST::Instruction> rhs = nullptr;

		if (lhs == nullptr)
			lhs = parseOperand(parsingInformations);
		if (nextOperator == nullptr)
			nextOperator = parseOperator(parsingInformations);
		while (nextOperator)
		{
			auto currentOperator = std::move(nextOperator);
			auto operatorParsingInformations = Parser::ParsingInformations{*currentOperator, scope, src, pos};

			currentOperator->addInstruction(std::move(lhs));
			rhs = parseOperand(operatorParsingInformations);
			nextOperator = parseOperator(operatorParsingInformations);
			if (!nextOperator || currentOperator->getPriority() > nextOperator->getPriority())
				currentOperator->addInstruction(std::move(rhs));
			else
			{
				currentOperator->addInstruction(parseOperation(operatorParsingInformations, std::move(rhs), std::move(nextOperator)));
				return currentOperator;
			}
			lhs = std::move(currentOperator);
		}
		return std::move(lhs);
	}

	std::unique_ptr<AST::Scope::Type::Value> Operator::interpret()
	{
		std::unique_ptr<AST::Scope::Type::Value> result;
		auto& operand0 = m_instructions[0];
		auto& operand1 = m_instructions[1];
		auto value0 = operand0->interpret();

		if (getName() == "=" && operand0->getInstructionType() == Variable::Type && !dynamic_cast<const AST::Scope::VariableScope&>(getScope().findScope(AST::Scope::VariableScopeType)).variableExists(dynamic_cast<Variable*>(operand0.get())->getName()))
			dynamic_cast<Variable*>(operand0.get())->setValue(std::make_unique<AST::Scope::Type::Number>());
		if (getName() == ".")
		{
			if (value0->getType() != AST::Scope::Type::Object::type)
				throw std::runtime_error{"L element avant le point doit etre un objet."};
			auto object = dynamic_cast<AST::Scope::Type::Object*>(value0.get());
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
			dynamic_cast<Variable*>(operand0.get())->setValue(result->cloneValue());
		return result;
	}

	std::unique_ptr<AST::Scope::Type::Value> Operator::doOp(const std::unique_ptr<AST::Scope::Type::Value>& val1, std::string_view op, const std::unique_ptr<AST::Scope::Type::Value>& val2)
	{
		static const auto operations = std::unordered_map<std::string, std::function<std::unique_ptr<AST::Scope::Type::Value>(const AST::Scope::Type::Value&, const AST::Scope::Type::Value&)>>{
			{ "=", []([[maybe_unused]] const auto& val1, const auto& val2) -> std::unique_ptr<AST::Scope::Type::Value> { return val2.cloneValue(); } },
			{ "+", [](const auto& val1, const auto& val2) -> std::unique_ptr<AST::Scope::Type::Value> { return std::unique_ptr<AST::Scope::Type::Value>(val1 + val2); } },
			{ "-", [](const auto& val1, const auto& val2) -> std::unique_ptr<AST::Scope::Type::Value> { return std::unique_ptr<AST::Scope::Type::Value>(val1 - val2); } },
			{ "*", [](const auto& val1, const auto& val2) -> std::unique_ptr<AST::Scope::Type::Value> { return std::unique_ptr<AST::Scope::Type::Value>(val1 * val2); } },
			{ "/", [](const auto& val1, const auto& val2) -> std::unique_ptr<AST::Scope::Type::Value> { return std::unique_ptr<AST::Scope::Type::Value>(val1 / val2); } },
			{ "%", [](const auto& val1, const auto& val2) -> std::unique_ptr<AST::Scope::Type::Value> { return std::unique_ptr<AST::Scope::Type::Value>(val1 % val2); } }
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
