project('proj_meta', 'c')

proj1_dep = dependency('proj1', fallback : ['proj1', 'proj1_dep'])
proj2_dep = dependency('proj2', fallback : ['proj2', 'proj2_dep'])
deps = [proj1_dep, proj2_dep]

executable('demo', 'src/main.c', dependencies : deps)
