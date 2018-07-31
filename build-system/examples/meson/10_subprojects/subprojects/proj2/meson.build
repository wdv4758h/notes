project('proj2', 'c')

proj2_inc = include_directories('include')
proj2_lib = shared_library(
  'proj2',
  'src/test2.c',
  include_directories : proj2_inc,
  install : false)

proj2_dep = declare_dependency(
  include_directories : proj2_inc,
  link_with : proj2_lib)
