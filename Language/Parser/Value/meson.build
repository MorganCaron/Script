cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	ast_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([])

headers = files([
	'include/Language/Parser/Value/FunctionCallParser.hpp',
	'include/Language/Parser/Value/NumberParser.hpp',
	'include/Language/Parser/Value/ParenthesisParser.hpp',
	'include/Language/Parser/Value/StringParser.hpp',
	'include/Language/Parser/Value/ValueParser.hpp',
	'include/Language/Parser/Value/VariableParser.hpp'
])

value_lib = library(
	'Value',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

value_dep = declare_dependency(
	link_with: value_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
