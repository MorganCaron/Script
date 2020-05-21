cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

subdir('Type')

public_dependencies = [
	cppUtils_dep,
	type_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([
	'src/BaseScope.cpp',
	'src/VariableScope.cpp'
])

headers = files([
	'include/Language/AST/Scope/BaseScope.hpp',
	'include/Language/AST/Scope/FileScope.hpp',
	'include/Language/AST/Scope/FunctionScope.hpp',
	'include/Language/AST/Scope/Object.hpp',
	'include/Language/AST/Scope/ObjectScope.hpp',
	'include/Language/AST/Scope/VariableScope.hpp'
])

scope_lib = library(
	'Scope',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

scope_dep = declare_dependency(
	link_with: scope_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
