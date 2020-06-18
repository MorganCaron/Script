cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	core_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([
	'src/BaseScope.cpp'
])

headers = files([
	'include/Language/AST/Scope/BaseScope.hpp'
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
