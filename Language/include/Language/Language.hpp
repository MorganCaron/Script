#pragma once

#include "AST.hpp"
#include "Bracket.hpp"
#include "ControlStructure.hpp"
#include "FunctionCall.hpp"
#include "FunctionStatement.hpp"
#include "Instruction.hpp"
#include "InstructionContainer.hpp"
#include "Interpreter.hpp"
#include "Object.hpp"
#include "Operator.hpp"
#include "Parser.hpp"
#include "Value.hpp"
#include "Variable.hpp"

#include <Language/Scope/FileScope.hpp>
#include <Language/Scope/FunctionScope.hpp>
#include <Language/Scope/ObjectScope.hpp>
#include <Language/Scope/BaseScope.hpp>
#include <Language/Scope/VariableScope.hpp>

#include <Language/Scope/Type/Function.hpp>
#include <Language/Scope/Type/Number.hpp>
#include <Language/Scope/Type/Object.hpp>
#include <Language/Scope/Type/String.hpp>
#include <Language/Scope/Type/Value.hpp>
