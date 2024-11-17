shardsinstaller_sources = [
  'main.c',
  'shardsinstaller-application.c',
  'shardsinstaller-window.c',
  'widgets/shardsinstaller-disk-entry.c',
  'pages/welcome/shardsinstaller-welcome.c',
  'pages/disk-selection/shardsinstaller-disk-selection.c',
  'pages/install-progress/shardsinstaller-install-progress.c',
  'utils/disks.c'
]

shardsinstaller_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.4'),
  dependency('udisks2')
]

shardsinstaller_sources += gnome.compile_resources('shardsinstaller-resources',
  'shardsinstaller.gresource.xml',
  c_name: 'shardsinstaller'
)

executable('shardsinstaller', shardsinstaller_sources,
  dependencies: shardsinstaller_deps,
       install: true,
)
