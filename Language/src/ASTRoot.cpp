#include <Language/ASTRoot.hpp>

#include <Language/Parser/Declaration/ClassParser.hpp>
#include <Language/Parser/Declaration/FunctionDeclarationParser.hpp>
#include <Language/Parser/Declaration/ImportDeclarationParser.hpp>
#include <Language/Parser/Declaration/NamespaceParser.hpp>

#include <Language/Parser/Instruction/BracketParser.hpp>
#include <Language/Parser/Instruction/ControlStructureParser.hpp>
#include <Language/Parser/Instruction/InstructionParser.hpp>
#include <Language/Parser/Instruction/ReturnParser.hpp>
#include <Language/Parser/Instruction/ValueParser.hpp>
#include <Language/Parser/Instruction/VariableDeclarationParser.hpp>

#include <Language/Parser/Value/FunctionCallParser.hpp>
#include <Language/Parser/Value/InstanceParser.hpp>
#include <Language/Parser/Value/NamespaceCallParser.hpp>
#include <Language/Parser/Value/NumberParser.hpp>
#include <Language/Parser/Value/ParenthesisParser.hpp>
#include <Language/Parser/Value/StringParser.hpp>
#include <Language/Parser/Value/ValueParser.hpp>
#include <Language/Parser/Value/VariableParser.hpp>

#include <Language/Parser/Operator/OperatorParser.hpp>
#include <Language/Parser/Operator/AssignmentParser.hpp>
#include <Language/Parser/Operator/AdditionParser.hpp>
#include <Language/Parser/Operator/MemberParser.hpp>

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

	void ASTRoot::parse(const std::string src, bool verbose)
	{
		auto pos = std::size_t{0};
		auto context = AST::ParsingTools::Context{*this, *this, CppUtils::Parser::Cursor{src, pos}, verbose};
		auto& cursor = context.cursor;
		const auto length = cursor.src.length();
		
		while (cursor.pos < length)
		{
			auto instruction = Parser::Declaration::parseDeclaration(context);
			if (instruction != nullptr)
			{
				addInstruction(std::move(instruction));
				context.skipSpacesAndComments();
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
		static const auto declarations = std::unordered_map<std::string, AST::ParsingTools::DeclarationParser>{
			{ "Class", &Parser::Declaration::parseClass },
			{ "Function declaration", &Parser::Declaration::parseFunctionDeclaration },
			{ "Import declaration", &Parser::Declaration::parseImportDeclaration },
			{ "Namespace", &Parser::Declaration::parseNamespace },
			{ "Variable declaration", &Parser::Instruction::parseVariableDeclaration }
		};
		addDeclarationParsers(declarations);

		static const auto instructions = std::unordered_map<std::string, AST::ParsingTools::InstructionParser>{
			{ "Bracket", &Parser::Instruction::parseBracket },
			{ "Control structure", &Parser::Instruction::parseControlStructure },
			{ "Return", &Parser::Instruction::parseReturn },
			{ "Value", &Parser::Instruction::parseValue },
			{ "Variable declaration", &Parser::Instruction::parseVariableDeclaration }
		};
		addInstructionParsers(instructions);

		static const auto values = std::unordered_map<std::string, AST::ParsingTools::ValueParser>{
			{ "Function call", &Parser::Value::parseFunctionCall },
			{ "Instance", &Parser::Value::parseInstance },
			{ "Namespace call", &Parser::Value::parseNamespaceCall },
			{ "Number", &Parser::Value::parseNumber },
			{ "Parenthesis", &Parser::Value::parseParenthesis },
			{ "String", &Parser::Value::parseString },
			{ "Variable", &Parser::Value::parseVariable }
		};
		addValueParsers(values);

		static const auto operators = std::unordered_map<std::string, AST::ParsingTools::OperatorParser>{
			{ "Assignment", &Parser::Operator::parseAssignment },
			{ "Addition", &Parser::Operator::parseAddition },
			{ "Member", &Parser::Operator::parseMember }
		};
		addOperatorParsers(operators);
	}
}
