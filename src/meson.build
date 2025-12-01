# Sources
sources = [
    'config.cpp',
	'csv.cpp',
	'file_to_string.cpp',
	'graph_coloring.cpp',
	'input.cpp',
	'log.cpp',
	'string_to_file.cpp'
]

source_files = files(sources)

inc = include_directories('.')

# Create main executable
executable('studiesschedule',
    source_files + files(['main.cpp']),
	dependencies:        deps,
    include_directories: inc,
	link_args:           linkargs,
    install:             true
)
