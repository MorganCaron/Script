cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	core_dep,
	scope_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([
	'src/VariableScope.cpp',
	'src/Variable.cpp',
	'src/VariableDeclaration.cpp'
])

headers = files([
	'include/Language/AST/Variable/VariableScope.hpp',
	'include/Language/AST/Variable/Variable.hpp',
	'include/Language/AST/Variable/VariableDeclaration.hpp'
])

variable_lib = library(
	'Variable',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

variable_dep = declare_dependency(
	link_with: variable_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
