project(
  'glass',
  'c',
  license: 'MIT',
  meson_version: '>=0.49.0',
  default_options: [
	  'c_std=c11',
	  'warning_level=2',
	  'werror=true',
  ],
)

add_project_arguments(
  [
	'-DWLR_USE_UNSTABLE',
	'-D_POSIX_C_SOURCE=200809L',

	'-Wno-unused-parameter',
	'-Wno-unused-result',
	'-Wno-missing-braces',
	'-Wundef',
	'-Wvla',
  ],
  language: 'c',
)

prefix = get_option('prefix')

git               = find_program('git', required: false)
wayland_protocols = dependency('wayland-protocols')
wayland_scanner   = dependency('wayland-scanner')
wayland_server    = dependency('wayland-server')
wlroots           = dependency('wlroots')
xkbcommon         = dependency('xkbcommon')

include = include_directories('include')

compiler = meson.get_compiler('c')
if compiler.get_id() == 'gcc' or compiler.get_id() == 'clang'
  add_project_arguments('-DUNUSED(x)=UNUSED_ ## x __attribute__((__unused__))', language: 'c')
else
  add_project_arguments('-DUNUSED(x)=UNUSED_ ## x', language: 'c')
endif

subdir('protocols')
subdir('glass')

