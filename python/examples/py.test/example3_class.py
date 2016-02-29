#!/usr/bin/env python

'''
test cases will be discovered by py.test by Python testing conventions
'''


class TestClass:
    def test_f(self):
        assert 42 == 42

    def test_g(self):
        assert " hello ".strip() == "hello"
