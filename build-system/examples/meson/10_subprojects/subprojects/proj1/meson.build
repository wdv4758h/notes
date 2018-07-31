project('proj1', 'c')

proj1_inc = include_directories('include')
proj1_lib = shared_library(
  'proj1',
  'src/test1.c',
  include_directories : proj1_inc,
  install : false)

proj1_dep = declare_dependency(
  include_directories : proj1_inc,
  link_with : proj1_lib)
