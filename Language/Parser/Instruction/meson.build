cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	ast_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([])

headers = files([
	'include/Language/Parser/Instruction/BracketParser.hpp',
	'include/Language/Parser/Instruction/ClassParser.hpp',
	'include/Language/Parser/Instruction/ControlStructureParser.hpp',
	'include/Language/Parser/Instruction/FunctionDeclarationParser.hpp',
	'include/Language/Parser/Instruction/ImportDeclarationParser.hpp',
	'include/Language/Parser/Instruction/InstructionParser.hpp',
	'include/Language/Parser/Instruction/ReturnParser.hpp',
	'include/Language/Parser/Instruction/VariableDeclarationParser.hpp'
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
