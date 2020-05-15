cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([
	'src/Value.cpp',
	'src/Number.cpp',
	'src/String.cpp'
])

headers = files([
	'include/Language/Scope/Type/Value.hpp',
	'include/Language/Scope/Type/Number.hpp',
	'include/Language/Scope/Type/String.hpp',
	'include/Language/Scope/Type/Function.hpp'
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
