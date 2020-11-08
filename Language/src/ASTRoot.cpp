#include <Language/ASTRoot.hpp>

#include <Language/Parser/Declaration/ClassParser.hpp>
#include <Language/Parser/Declaration/FunctionDeclarationParser.hpp>
#include <Language/Parser/Declaration/ImportDeclarationParser.hpp>
#include <Language/Parser/Declaration/NamespaceDeclarationParser.hpp>

#include <Language/Parser/Instruction/BracketParser.hpp>
#include <Language/Parser/Instruction/ControlStructureParser.hpp>
#include <Language/Parser/Instruction/InstructionParser.hpp>
#include <Language/Parser/Instruction/OperationParser.hpp>
#include <Language/Parser/Instruction/ReturnParser.hpp>
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
#include <Language/Parser/Operator/AdditionParser.hpp>
#include <Language/Parser/Operator/AssignmentParser.hpp>
#include <Language/Parser/Operator/EqualityParser.hpp>
#include <Language/Parser/Operator/MemberParser.hpp>
#include <Language/Parser/Operator/MultiplicationParser.hpp>
#include <Language/Parser/Operator/NotEqualityParser.hpp>

#include <Language/AST/Function/FunctionSignature.hpp>

namespace Language
{
	ASTRoot::ASTRoot()
	{
		initNativeParsers();
	}

	ASTRoot::ASTRoot(std::string src)
	{
		initNativeParsers();
		parse(std::move(src));
	}

	void ASTRoot::parse(std::string_view src, bool verbose)
	{
		auto pos = std::size_t{0};
		auto context = AST::ParsingTools::Context{*this, *this, CppUtils::Language::Parser::Cursor{src.data(), pos}, verbose};
		auto& cursor = context.cursor;
		const auto length = cursor.src.length();
		
		while (cursor.pos < length)
		{
			auto declaration = Parser::Declaration::parseDeclaration(context);
			if (declaration != nullptr)
			{
				declaration->indexe();
				addInstruction(std::move(declaration));
				context.skipSpacesAndComments();
			}
		}
	}

	std::unique_ptr<AST::Type::IValue> ASTRoot::interpret()
	{
		const auto mainFunctionSignature = AST::Function::FunctionSignature{"main", {}};
		if (!functionExists(mainFunctionSignature))
			throw std::runtime_error{"No entry point found: The main function is missing."};
		const auto& mainFunction = getFunction(mainFunctionSignature);
		return mainFunction.function({});
	}

	[[nodiscard]] const CppUtils::Type::TypeId& ASTRoot::getReturnType() const
	{
		const auto mainFunctionSignature = AST::Function::FunctionSignature{"main", {}};
		if (!functionExists(mainFunctionSignature))
			throw std::runtime_error{"No entry point found: The main function is missing."};
		const auto& mainFunction = getFunction(mainFunctionSignature);
		return mainFunction.returnType;
	}

	void ASTRoot::initNativeParsers()
	{
		declarationParsers = std::vector<AST::ParsingTools::NamedParser<AST::ParsingTools::DeclarationParser>>{
			{ "Class", &Parser::Declaration::parseClass },
			{ "Function declaration", &Parser::Declaration::parseFunctionDeclaration },
			{ "Import declaration", &Parser::Declaration::parseImportDeclaration },
			{ "Namespace declaration", &Parser::Declaration::parseNamespaceDeclaration },
			{ "Variable declaration", &Parser::Instruction::parseVariableDeclaration }
		};

		instructionParsers = std::vector<AST::ParsingTools::NamedParser<AST::ParsingTools::InstructionParser>>{
			{ "Bracket", &Parser::Instruction::parseBracket },
			{ "Control structure", &Parser::Instruction::parseControlStructure },
			{ "Return", &Parser::Instruction::parseReturn },
			{ "Variable declaration", &Parser::Instruction::parseVariableDeclaration },
			{ "Operation", &Parser::Instruction::parseOperation }
		};

		valueParsers = std::vector<AST::ParsingTools::NamedParser<AST::ParsingTools::ValueParser>>{
			{ "Function call", &Parser::Value::parseFunctionCall },
			{ "Instance", &Parser::Value::parseInstance },
			{ "Namespace call", &Parser::Value::parseNamespaceCall },
			{ "Number", &Parser::Value::parseNumber },
			{ "Parenthesis", &Parser::Value::parseParenthesis },
			{ "String", &Parser::Value::parseString },
			{ "Variable", &Parser::Value::parseVariable }
		};
		
		operatorParsers = std::vector<AST::ParsingTools::NamedParser<AST::ParsingTools::OperatorParser>>{
			{ "Addition", &Parser::Operator::parseAddition },
			{ "Assignment", &Parser::Operator::parseAssignment },
			{ "Equality", &Parser::Operator::parseEquality },
			{ "Member", &Parser::Operator::parseMember },
			{ "Multiplication", &Parser::Operator::parseMultiplication },
			{ "NotEquality", &Parser::Operator::parseNotEquality }
		};
	}
}
