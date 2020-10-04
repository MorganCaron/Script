cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([])

headers = files([
	'include/Language/AST/Type/Boolean.hpp',
#	'include/Language/AST/Type/Function.hpp',
	'include/Language/AST/Type/Number.hpp',
	'include/Language/AST/Type/String.hpp',
	'include/Language/AST/Type/Type.hpp'
])

type_lib = library(
	'Type',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

type_dep = declare_dependency(
	link_with: type_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
