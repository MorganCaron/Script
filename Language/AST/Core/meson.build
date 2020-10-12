cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	type_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([])

headers = files([
	'include/Language/AST/Core/Instruction.hpp',
	'include/Language/AST/Core/InstructionContainer.hpp'
])

core_lib = library(
	'Core',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

core_dep = declare_dependency(
	link_with: core_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
