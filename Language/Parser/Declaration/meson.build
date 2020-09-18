cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	ast_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([])

headers = files([
	'include/Language/Parser/Declaration/ClassParser.hpp',
	'include/Language/Parser/Declaration/FunctionDeclarationParser.hpp',
	'include/Language/Parser/Declaration/ImportDeclarationParser.hpp',
	'include/Language/Parser/Declaration/NamespaceParser.hpp'
])

declaration_lib = library(
	'Declaration',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

declaration_dep = declare_dependency(
	link_with: declaration_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
