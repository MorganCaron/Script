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
	'include/Language/Scope/BaseScope.hpp',
	'include/Language/Scope/VariableScope.hpp',
	'include/Language/Scope/FunctionScope.hpp',
	'include/Language/Scope/ObjectScope.hpp',
	'include/Language/Scope/FileScope.hpp',
	'include/Language/Scope/Object.hpp'
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
