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
	'include/Language/AST/Operator/Addition.hpp',
	'include/Language/AST/Operator/Assignment.hpp',
	'include/Language/AST/Operator/Equality.hpp',
	'include/Language/AST/Operator/Member.hpp',
	'include/Language/AST/Operator/Multiplication.hpp',
	'include/Language/AST/Operator/NotEquality.hpp',
	'include/Language/AST/Operator/Operator.hpp'
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
