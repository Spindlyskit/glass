glass_sources = files(
  'main.c',
  'server.c',
  'desktop/output.c',
)

glass_deps = [
  protocols_server,
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
