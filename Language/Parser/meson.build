cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

subdir('Value')
subdir('Operator')
subdir('Instruction')
subdir('Declaration')

public_dependencies = [
	cppUtils_dep,
	ast_dep,
	value_dep,
	operator_dep,
	instruction_dep,
	declaration_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([])

headers = files([])

parser_lib = library(
	'Parser',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

parser_dep = declare_dependency(
	link_with: parser_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
