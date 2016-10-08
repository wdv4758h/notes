########################################
# run test cases
########################################

py.test test_mod.py   # run tests in module
py.test somepath      # run all tests below somepath
py.test -k stringexpr # only run tests with names that match the
                      # the "string expression", e.g. "MyClass and not method"
                      # will select TestMyClass.test_something
                      # but not TestMyClass.test_method_simple
py.test test_mod.py::test_func  # only run tests that match the "node ID",
                                # e.g "test_mod.py::test_func" will select
                                # only test_func in test_mod.py
py.test test_mod.py::TestClass::test_method  # run a single method in
                                             # a single class


########################################
# Information
########################################

py.test --showlocals # show local variables in tracebacks
py.test -l           # show local variables (shortcut)

py.test --tb=long    # the default informative traceback formatting
py.test --tb=native  # the Python standard library formatting
py.test --tb=short   # a shorter traceback format
py.test --tb=line    # only one line per failure


########################################
# PDB
########################################

py.test --pdb
py.test -x --pdb    # drop to PDB on first failure, then end test session
py.test --pdb --maxfail=3   # drop to PDB for first three failures


########################################
# Profiling
########################################

py.test --durations=10  # list slowest 10 test durations


########################################
# Generate Result Files
########################################

py.test --junitxml=path     # XML
py.test --resultlog=path    # plain text
                            # used : http://buildbot.pypy.org/summary


########################################
# Disable Plugins
########################################

py.test -p no:doctest
