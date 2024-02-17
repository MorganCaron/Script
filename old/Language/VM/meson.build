cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

public_dependencies = [
	cppUtils_dep
]
private_dependencies = []

includeDir = include_directories(['include/', '.'])

sources = files([])

headers = files([
	'include/Script/Language/VM/Operations.hpp',
	'include/Script/Language/VM/VM.hpp'
])

script_language_vm_lib = library(
	'ScriptLanguageVM',
	sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

script_language_vm_dep = declare_dependency(
	link_with: script_language_vm_lib,
	include_directories: includeDir,
	dependencies: public_dependencies
)
