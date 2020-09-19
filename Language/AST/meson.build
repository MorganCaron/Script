cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

subdir('Type')
subdir('Core')
subdir('Scope')
subdir('Variable')
subdir('Function')
subdir('Object')
subdir('Operator')
subdir('Value')
subdir('Instruction')
subdir('Namespace')
subdir('ParsingTools')

public_dependencies = [
	instruction_dep,
	parsingTools_dep,
	namespace_dep
]
private_dependencies = [
	cppUtils_dep
]

includeDir = include_directories(['.'])

sources = files([])

headers = files([])

ast_lib = library(
	'AST',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

ast_dep = declare_dependency(
	link_with: ast_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
