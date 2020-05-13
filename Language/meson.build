cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

subdir('Scope')

public_dependencies = [
	cppUtils_dep,
	scope_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([
	'src/AST.cpp',
	'src/Bracket.cpp',
	'src/ControlStructure.cpp',
	'src/FunctionCall.cpp',
	'src/FunctionStatement.cpp',
	'src/Object.cpp',
	'src/Operator.cpp',
	'src/Value.cpp',
	'src/Variable.cpp',
	'src/Return.cpp'
])

headers = files([
	'include/Language/AST.hpp',
	'include/Language/Bracket.hpp',
	'include/Language/ControlStructure.hpp',
	'include/Language/FunctionCall.hpp',
	'include/Language/FunctionStatement.hpp',
	'include/Language/Instruction.hpp',
	'include/Language/InstructionContainer.hpp',
	'include/Language/Interpreter.hpp',
	'include/Language/Object.hpp',
	'include/Language/Operator.hpp',
	'include/Language/Parser.hpp',
	'include/Language/Value.hpp',
	'include/Language/Variable.hpp',
	'include/Language/Return.hpp'
])

language_lib = library(
	'Language',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

language_dep = declare_dependency(
	link_with: language_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
