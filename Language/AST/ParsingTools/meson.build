cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	file_dep,
	value_dep,
	instruction_dep,
	operator_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([])

headers = files([
	'include/Language/AST/ParsingTools/Cursor.hpp',
	'include/Language/AST/ParsingTools/ParserScope.hpp'
])

parsingTools_lib = library(
	'ParsingTools',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

parsingTools_dep = declare_dependency(
	link_with: parsingTools_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
