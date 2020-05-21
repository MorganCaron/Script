cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

subdir('Scope')

public_dependencies = [
	cppUtils_dep,
	scope_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([
	
])

headers = files([
	'include/Language/AST/Instruction.hpp',
	'include/Language/AST/InstructionContainer.hpp',
	'include/Language/AST/Interpreter.hpp'
])

ast_lib = library(
	'AST',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

ast_dep = declare_dependency(
	link_with: ast_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
