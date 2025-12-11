# Sources
sources = [
    'config.cpp',
	'csv.cpp',
	'file_to_string.cpp',
	'graph_coloring.cpp',
	'input.cpp',
	'output.cpp',
	'prepare_schedule.cpp',
	'separate_assignments.cpp',
	'solve.cpp',
	'solve_graph_adaptor.cpp',
	'string_to_file.cpp'
]

source_files = files(sources)

inc = include_directories('.')

# Create main executable
executable('studiesschedule',
    source_files + files(['main.cpp', 'log.cpp']),
	dependencies:        deps,
    include_directories: inc,
	link_args:           linkargs,
    install:             true
)
