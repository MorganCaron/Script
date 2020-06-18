#pragma once

#include <Language/AST/Core/Instruction.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Core/Interpreter.hpp>

#include <Language/AST/File/FileScope.hpp>
#include <Language/AST/File/ImportDeclaration.hpp>

#include <Language/AST/Function/FunctionDeclaration.hpp>
#include <Language/AST/Function/FunctionScope.hpp>

#include <Language/AST/Instruction/Bracket.hpp>
#include <Language/AST/Instruction/ControlStructure.hpp>
#include <Language/AST/Instruction/FunctionCall.hpp>
#include <Language/AST/Instruction/Operator.hpp>
#include <Language/AST/Instruction/Return.hpp>

#include <Language/AST/Object/Class.hpp>
#include <Language/AST/Object/Instance.hpp>
#include <Language/AST/Object/ObjectScope.hpp>

#include <Language/AST/ParsingTools/ParserScope.hpp>
#include <Language/AST/ParsingTools/Cursor.hpp>

#include <Language/AST/Value/Number.hpp>
#include <Language/AST/Value/String.hpp>

#include <Language/AST/Scope/BaseScope.hpp>

#include <Language/AST/Type/Function.hpp>
#include <Language/AST/Type/Number.hpp>
#include <Language/AST/Type/String.hpp>
#include <Language/AST/Type/Type.hpp>

#include <Language/AST/Variable/Variable.hpp>
#include <Language/AST/Variable/VariableDeclaration.hpp>
#include <Language/AST/Variable/VariableScope.hpp>

#include <Language/Parser/Instruction/BracketParser.hpp>
#include <Language/Parser/Instruction/ClassParser.hpp>
#include <Language/Parser/Instruction/ControlStructureParser.hpp>
#include <Language/Parser/Instruction/FunctionDeclarationParser.hpp>
#include <Language/Parser/Instruction/ImportDeclarationParser.hpp>
#include <Language/Parser/Instruction/InstructionParser.hpp>
#include <Language/Parser/Instruction/ReturnParser.hpp>
#include <Language/Parser/Instruction/VariableDeclarationParser.hpp>

#include <Language/Parser/Operator/OperatorParser.hpp>
#include <Language/Parser/Operator/AssignmentParser.hpp>
#include <Language/Parser/Operator/AdditionParser.hpp>

#include <Language/Parser/Value/FunctionCallParser.hpp>
#include <Language/Parser/Value/NumberParser.hpp>
#include <Language/Parser/Value/ParenthesisParser.hpp>
#include <Language/Parser/Value/StringParser.hpp>
#include <Language/Parser/Value/ValueParser.hpp>
#include <Language/Parser/Value/VariableParser.hpp>

#include <Language/ASTRoot.hpp>
