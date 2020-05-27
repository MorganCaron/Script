project('Script',
	'cpp',
	version: '0.0.0',
	license: 'LGPL3',
	default_options: [
		'cpp_std=c++2a',
		'warning_level=3',
		'optimization=3',
		'werror=true'
	]
)

version = meson.project_version()
versionArray = version.split('.')

configuration = {
	'NAME': meson.project_name(),
	'DESCRIPTION': 'Script is an object-oriented interpreted programming language.',
	'VERSION': version,
	'VERSION_MAJOR': versionArray[0],
	'VERSION_MINOR': versionArray[1],
	'VERSION_PATCH': versionArray[2],
	'LICENSE': 'LGPL3',
	'COMPANY_NAME': 'Morgan Caron',
	'COMMENT': 'https://github.com/MorganCaron/Script',
	'ENABLE_LOGS': 1,
	'ICON': 'logo-glow.ico'
}

configure_file(
	input: 'config.in.hpp',
	output: 'config.hpp',
	configuration: configuration
)

cppUtils_dep = dependency('CppUtils', fallback: ['CppUtils', 'cppUtils_dep'])

subdir('res')
subdir('Language')

public_dependencies = [
	cppUtils_dep,
	language_dep
]
private_dependencies = [
]

includeDir = include_directories(['include', 'res', '.'])

sources = files([

])

headers = files([
	'include/Script.hpp'
])

script_exe = executable(
	'Script',
	sources: ['src/main.cpp'] + sources + headers + resources,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies,
	link_args: '-Wl,--out-implib=libScript.dll.a'
)

script_dep = declare_dependency(
	link_with: script_exe,
	include_directories: includeDir,
	dependencies: public_dependencies
)

unitTests_exe = executable(
	'UnitTests',
	sources: ['src/tests.cpp'] + sources + headers + resources,
	include_directories: includeDir,
	dependencies: public_dependencies + private_dependencies
)

configure_file(
	copy: true,
	input: 'program.script',
	output: 'program.script'
)

test('Unit tests', unitTests_exe)
