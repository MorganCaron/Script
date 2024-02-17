if host_machine.system() == 'windows'
	windows = import('windows')

	resourceFile = configure_file(
		input: 'resources.in.rc',
		output: 'resources.rc',
		configuration: configuration
	)

	resourceFileCompiled = windows.compile_resources(
		resourceFile,
		depend_files: configuration['ICON'],
		include_directories: include_directories('./')
	)

	resources = [
		resourceFileCompiled,
		'res/resources.hpp'
	]
else
	resources = []
endif
