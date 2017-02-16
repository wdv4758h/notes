import pytest


@pytest.fixture()
def myitem():
    return "this is my item"

def pytest_assertrepr_compare(op, left, right):
    if isinstance(left, int) and isinstance(right, int) and op == "==":
        return ['Comparing number:',
                '   vals: %s != %s' % (left, right)]
