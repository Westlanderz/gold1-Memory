project('Memory viewer', 'cpp', default_options : ['warning_level=3', 'werror=false'], version: '0.1.0')

cpp_compiler = meson.get_compiler('cpp')
add_project_arguments('--std=c++20', '-c', '-fcoroutines', '-ggdb', language: 'cpp')
add_project_arguments('-Wno-pedantic', '-Wshadow', '-Wno-pointer-arith', '-Wcast-align', '-Wwrite-strings', '-Wmissing-declarations', '-Wredundant-decls', '-Winline', '-Wno-long-long', '-Wconversion', language: 'cpp')
add_project_arguments('-Wno-sign-compare', '-Wno-missing-field-initializers', '-Wno-unused-parameter', '-Wno-unused-variable', '-Wno-format-extra-args', '-Wno-unused-but-set-variable', '-Wno-conversion', '-fno-omit-frame-pointer', '-Wno-missing-declarations', language: 'cpp')
add_project_link_arguments('-omemview', language: 'cpp')

subdir('src/')