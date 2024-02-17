cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	core_dep,
	scope_dep,
	variable_dep,
	object_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([
	'src/Bracket.cpp',
	'src/ControlStructure.cpp',
	'src/FunctionCall.cpp'
])

headers = files([
	'include/Language/AST/Instruction/Bracket.hpp',
	'include/Language/AST/Instruction/ControlStructure.hpp',
	'include/Language/AST/Instruction/FunctionCall.hpp',
	'include/Language/AST/Instruction/Return.hpp'
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
