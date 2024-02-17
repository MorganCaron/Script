#pragma once

#include <CppUtils.hpp>

namespace Script::Language
{
	class Grammar final
	{
	public:
		Grammar()
		{
			using namespace std::literals;
			using namespace CppUtils::Type::Literals;
			m_grammarLexer.addParsingFunction("spaceParser"_token, CppUtils::Language::Parser::spaceParser<CppUtils::Type::Token, float>);
			m_grammarLexer.addParsingFunction("keywordParser"_token, CppUtils::Language::Parser::keywordParser<CppUtils::Type::Token, float>);
			m_grammarLexer.addParsingFunction("quoteParser"_token, CppUtils::Language::Parser::quoteParser<CppUtils::Type::Token, float>);
			m_grammarLexer.addParsingFunction("floatParser"_token, CppUtils::Language::Parser::floatParser<CppUtils::Type::Token, float>);
			
			static constexpr auto grammarSrc = "\
			main: (_declaration >= 0) spaceParser;\
			\
			_declaration: spaceParser (namespaceDeclaration || classDeclaration || functionDeclaration || _variableDeclarationWithSemicolon);\
			_variableDeclarationWithSemicolon: variableDeclaration spaceParser ';';\
			_instruction: spaceParser (returnStatement || functionCall || variableDeclaration || operation) spaceParser ';';\
			_type: spaceParser keywordParser;\
			_value: spaceParser (string || number || functionCall || variableCall);\
			_operator: spaceParser (_comparisonOperator || incrementOperator || decrementOperator || _arithmeticOperator || assignmentOperator);\
			_comparisonOperator: (equalOperator || notEqualOperator);\
			_arithmeticOperator: (additionOperator || subtractionOperator || multiplicationOperator || divisionOperator || moduloOperator);\
			\
			equalOperator: '==';\
			notEqualOperator: '!=';\
			incrementOperator: '++';\
			decrementOperator: '--';\
			assignmentOperator: '=';\
			additionOperator: '+';\
			subtractionOperator: '-';\
			multiplicationOperator: '*';\
			divisionOperator: '/';\
			moduloOperator: '%';\
			\
			namespaceDeclaration: 'namespace' spaceParser keywordParser namespaceDeclarationContent;\
			namespaceDeclarationContent: spaceParser '{' (_declaration >= 0) spaceParser '}';\
			\
			classDeclaration: 'class' spaceParser keywordParser classDeclarationContent;\
			classDeclarationContent: spaceParser '{' (declarationsInAClass >= 0) spaceParser '}';\
			declarationsInAClass: spaceParser staticKeyword spaceParser (functionDeclaration || _variableDeclarationWithSemicolon);\
			staticKeyword: 'static';\
			\
			functionDeclaration: 'function' spaceParser keywordParser argumentsDeclaration typeSpecification functionDeclarationContent;\
			typeSpecification: spaceParser ':' spaceParser _type;\
			valueSpecification: spaceParser '=' operation;\
			argumentsDeclaration: '(' !_argumentsDeclaration spaceParser ')';\
			_argumentsDeclaration: variableDeclaration !_secondArgumentDeclaration;\
			_secondArgumentDeclaration: spaceParser ',' _argumentsDeclaration;\
			functionDeclarationContent: (_functionDeclarationAccolades || _instruction);\
			_functionDeclarationAccolades: spaceParser '{' (_instruction >= 0) spaceParser '}';\
			\
			variableDeclaration: (constKeyword || letKeyword) spaceParser keywordParser !typeSpecification !valueSpecification;\
			constKeyword: 'const';\
			letKeyword: 'let';\
			\
			returnStatement: 'return' operation;\
			\
			functionCall: keywordParser arguments;\
			arguments: '(' !_arguments spaceParser ')';\
			_arguments: operation !_secondArgument;\
			_secondArgument: spaceParser ',' _arguments;\
			\
			operation: _operand;\
			_operand: _value !_secondOperand;\
			_secondOperand: spaceParser _operator _operand;\
			\
			string: quoteParser;\
			number: floatParser;\
			variableCall: keywordParser;\
			"sv;
			m_grammarLexer.parseGrammar(grammarSrc);
		}

		[[nodiscard]] CppUtils::Parser::ASTNode<CppUtils::Type::Token, float> parse(std::string_view src) const
		{
			using namespace CppUtils::Type::Literals;
			return m_grammarLexer.parseLanguage("main"_token, src);
		}

	private:
		CppUtils::Language::Lexer::GrammarLexer<CppUtils::Type::Token, float> m_grammarLexer;
	};
}
