cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep,
	function_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([
	'src/Class.cpp',
	'src/Instantiation.cpp'
])

headers = files([
	'include/Language/AST/Object/Class.hpp',
	'include/Language/AST/Object/Instance.hpp',
	'include/Language/AST/Object/Type.hpp',
	'include/Language/AST/Object/ObjectScope.hpp',
	'include/Language/AST/Object/Instantiation.hpp'
])

object_lib = library(
	'Object',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

object_dep = declare_dependency(
	link_with: object_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
