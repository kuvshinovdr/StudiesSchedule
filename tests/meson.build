# Test sources
tests = [
    'test_config.cpp',
	'test_csv.cpp',
	'test_graph_coloring.cpp',
	'test_input.cpp',
	'test_output.cpp',
	'test_prepare_schedule.cpp',
	'test_separate_assignments.cpp',
	'test_solve.cpp',
	'test_solve_graph_adaptor.cpp',
	'test_string_operations.cpp'
]

test_sources = files(tests)

# Build test executable
# doctest provides its own main() if you define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN,
# but it's cleaner to let the subproject handle it via the dependency.
studiesschedule_tests = executable('studiesschedule_tests',
    source_files + test_sources + files(['test_main.cpp', 'log_test_implementation.cpp']),
    dependencies:        deps,
    include_directories: inc,
    link_args:           linkargs,
    install:             false
)

# Register test
test('unit-tests', studiesschedule_tests)