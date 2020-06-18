cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

subdir('AST')
subdir('Parser')

public_dependencies = [
	cppUtils_dep,
	parser_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([
	'src/ASTRoot.cpp'
])

headers = files([
	'include/Language/ASTRoot.hpp',
	'include/Language/Language.hpp'
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
