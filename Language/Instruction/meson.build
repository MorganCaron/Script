cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	scope_dep,
	parser_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([
	'src/Bracket.cpp',
	'src/ControlStructure.cpp',
	'src/FunctionCall.cpp',
	'src/FunctionDeclaration.cpp',
	'src/ImportDeclaration.cpp',
	'src/Object.cpp',
	'src/Operator.cpp',
	'src/Return.cpp',
	'src/Value.cpp',
	'src/Variable.cpp',
	'src/VariableDeclaration.cpp'
])

headers = files([
	'include/Language/Instruction/Bracket.hpp',
	'include/Language/Instruction/ControlStructure.hpp',
	'include/Language/Instruction/FunctionCall.hpp',
	'include/Language/Instruction/FunctionDeclaration.hpp',
	'include/Language/Instruction/ImportDeclaration.hpp',
	'include/Language/Instruction/Object.hpp',
	'include/Language/Instruction/Operator.hpp',
	'include/Language/Instruction/Return.hpp',
	'include/Language/Instruction/Value.hpp',
	'include/Language/Instruction/Variable.hpp',
	'include/Language/Instruction/VariableDeclaration.hpp'
])

instruction_lib = library(
	'Instruction',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

instruction_dep = declare_dependency(
	link_with: instruction_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
