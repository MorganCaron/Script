cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	variable_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([
	'src/FunctionDeclaration.cpp'
])

headers = files([
	'include/Language/AST/Function/Function.hpp',
	'include/Language/AST/Function/FunctionScope.hpp',
	'include/Language/AST/Function/FunctionDeclaration.hpp'
])

function_lib = library(
	'Function',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

function_dep = declare_dependency(
	link_with: function_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
