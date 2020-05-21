cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	ast_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([
	'src/Parser.cpp'
])

headers = files([
	'include/Language/AST/Scope/InstructionScope.hpp',
	'include/Language/Parser/Number.hpp',
	'include/Language/Parser/Parser.hpp',
	'include/Language/Parser/String.hpp'
])

parser_lib = library(
	'Parser',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

parser_dep = declare_dependency(
	link_with: parser_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
