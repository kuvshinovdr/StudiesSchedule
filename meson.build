# Project heading.
project('StudiesSchedule', 'cpp',
        version: '1.0',
        default_options: [
            'cpp_std=c++23',
            'warning_level=everything',
		    'b_ndebug=if-release',
        ]
)

# Dependencies.
doctest_dep = dependency('doctest', fallback : ['doctest', 'doctest_dep'])
deps = [doctest_dep]

# Enforce C++23 support and GCC ≥ 15 for std::println.
cc = meson.get_compiler('cpp')

if cc.get_id() == 'gcc'
    if cc.version().version_compare('<15')
        error('GCC >= 15 is required for std::println (C++23)')
    endif
elif cc.get_id() == 'clang'
    # Clang doesn't yet implement std::println in standard library (as of 2025),
    # so we assume you're using GCC. If you plan to support Clang later,
    # you may need libc++ experimental support or feature guards.
    warning('Clang support for std::println is not guaranteed.')
endif

linkargs = []

# Optional: link libstdc++exp only for GCC.
if cc.get_id() == 'gcc'
    linkargs = ['-lstdc++exp']
endif

subdir('src')
subdir('tests')