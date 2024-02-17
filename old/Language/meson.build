cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([

])

headers = files([
	'include/Script/Language/Grammar.hpp',
	'include/Script/Language/Language.hpp'
])

language_lib = library(
	'Language',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

language_dep = declare_dependency(
	link_with: language_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
