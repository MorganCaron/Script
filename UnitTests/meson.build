public_dependencies = [
	cppUtils_dep,
	language_dep
]
private_dependencies = [
]

includeDir = include_directories(['../', '../include/', 'include/', '.'])

sources = files([
	'src/main.cpp'
])

headers = files([
	'../include/Script.hpp',
	'include/UnitTests/Class.hpp',
	'include/UnitTests/Function.hpp',
	'include/UnitTests/Namespace.hpp',
	'include/UnitTests/Operation.hpp',
	'include/UnitTests/Variable.hpp'
])

unitTests_exe = executable(
	'UnitTests',
	sources: sources + headers,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

test('Unit tests', unitTests_exe)
