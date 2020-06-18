#include <Language/ASTRoot.hpp>

#include <Language/Parser/Instruction/BracketParser.hpp>
#include <Language/Parser/Instruction/ClassParser.hpp>
#include <Language/Parser/Instruction/ControlStructureParser.hpp>
#include <Language/Parser/Instruction/FunctionDeclarationParser.hpp>
#include <Language/Parser/Instruction/ImportDeclarationParser.hpp>
#include <Language/Parser/Instruction/InstructionParser.hpp>
#include <Language/Parser/Instruction/ReturnParser.hpp>
#include <Language/Parser/Instruction/VariableDeclarationParser.hpp>

#include <Language/Parser/Value/FunctionCallParser.hpp>
#include <Language/Parser/Value/NumberParser.hpp>
#include <Language/Parser/Value/ParenthesisParser.hpp>
#include <Language/Parser/Value/StringParser.hpp>
#include <Language/Parser/Value/ValueParser.hpp>
#include <Language/Parser/Value/VariableParser.hpp>

#include <Language/Parser/Operator/OperatorParser.hpp>
#include <Language/Parser/Operator/AssignmentParser.hpp>
#include <Language/Parser/Operator/AdditionParser.hpp>

namespace Language
{
	ASTRoot::ASTRoot()
	{
		addNativeRules();
	}

	ASTRoot::ASTRoot(std::string src)
	{
		addNativeRules();
		parse(std::move(src));
	}

	void ASTRoot::parse(const std::string src)
	{
		auto pos = std::size_t{0};
		auto cursor = AST::ParsingTools::Cursor{*this, *this, src, pos};
		const auto length = cursor.src.length();
		
		while (cursor.pos < length)
		{
			auto instruction = Parser::Instruction::parseInstruction(cursor);
			if (instruction != nullptr)
			{
				addInstruction(std::move(instruction));
				cursor.skipSpaces();
			}
		}
	}

	void ASTRoot::indexe()
	{
		for (auto& instruction : m_instructions)
			instruction->indexe();
	}

	void ASTRoot::addNativeRules()
	{
		static const auto instructions = std::unordered_map<std::string, AST::ParsingTools::InstructionParser>{
			{ "Bracket", &Parser::Instruction::parseBracket },
			{ "Class", &Parser::Instruction::parseClass },
			{ "Control structure", &Parser::Instruction::parseControlStructure },
			{ "Function declaration", &Parser::Instruction::parseFunctionDeclaration },
			{ "Import declaration", &Parser::Instruction::parseImportDeclaration },
			{ "Value", &Parser::Value::parseValue },
			{ "Return", &Parser::Instruction::parseReturn },
			{ "Variable declaration", &Parser::Instruction::parseVariableDeclaration }
		};
		addInstructionParsers(instructions);

		static const auto values = std::unordered_map<std::string, AST::ParsingTools::ValueParser>{
			{ "Function call", &Parser::Value::parseFunctionCall },
			{ "Number", &Parser::Value::parseNumber },
			{ "Parenthesis", &Parser::Value::parseParenthesis },
			{ "String", &Parser::Value::parseString },
			{ "Variable", &Parser::Value::parseVariable }
		};
		addValueParsers(values);

		static const auto operators = std::unordered_map<std::string, AST::ParsingTools::OperatorParser>{
			{ "Assignment", &Parser::Operator::parseAssignment },
			{ "Addition", &Parser::Operator::parseAddition }
		};
		addOperatorParsers(operators);
	}
}
