cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	core_dep,
	scope_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([])

headers = files([
	'include/Language/AST/Value/Number.hpp',
	'include/Language/AST/Value/Value.hpp',
	'include/Language/AST/Value/String.hpp'
])

value_lib = library(
	'Value',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

value_dep = declare_dependency(
	link_with: value_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
