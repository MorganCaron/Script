cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	object_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([])

headers = files([
	'include/Language/AST/File/FileScope.hpp',
	'include/Language/AST/File/ImportDeclaration.hpp'
])

file_lib = library(
	'File',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

file_dep = declare_dependency(
	link_with: file_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
