glass_sources = files(
  'main.c',
  'server.c',
  'desktop/output.c',
)

glass_deps = [
  wayland_protocols,
  wayland_scanner,
  wayland_server,
  wlroots,
  xkbcommon,
]

executable(
  'glass',
  glass_sources,
  include_directories: [include],
  dependencies: glass_deps,
  install: true,
)
