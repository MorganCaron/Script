cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	ast_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([])

headers = files([
	'include/Language/Parser/Operator/AdditionParser.hpp',
	'include/Language/Parser/Operator/AssignmentParser.hpp',
	'include/Language/Parser/Operator/EqualityParser.hpp',
	'include/Language/Parser/Operator/MemberParser.hpp',
	'include/Language/Parser/Operator/MultiplicationParser.hpp',
	'include/Language/Parser/Operator/NotEqualityParser.hpp',
	'include/Language/Parser/Operator/OperatorParser.hpp'
])

operator_lib = library(
	'Operand',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

operator_dep = declare_dependency(
	link_with: operator_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
