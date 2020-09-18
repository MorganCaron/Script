cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	object_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([
	'src/NamespaceDeclaration.cpp'
])

headers = files([
	'include/Language/AST/Namespace/ImportDeclaration.hpp',
	'include/Language/AST/Namespace/NamespaceCall.hpp',
	'include/Language/AST/Namespace/NamespaceDeclaration.hpp',
	'include/Language/AST/Namespace/NamespaceScope.hpp'
])

namespace_lib = library(
	'Namespace',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

namespace_dep = declare_dependency(
	link_with: namespace_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
