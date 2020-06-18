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
	'include/Language/AST/Operator/Assignment.hpp',
	'include/Language/AST/Operator/Addition.hpp'
])

operator_lib = library(
	'Operator',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

operator_dep = declare_dependency(
	link_with: operator_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)