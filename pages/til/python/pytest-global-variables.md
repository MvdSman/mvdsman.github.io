# PyTest: Global variables

## How To

You can instantiate global variables in PyTest by using the `pytest_configure()` function in `conftest.py`.

> **WARNING: This is a stopgap measure implemented by PyTest.**

### Instantiate global variables

1. Make sure a `conftest.py` file exists and is used by the called tests
2. In the `conftest.py` file, create the following definition:
   ```python
   def pytest_configure():
       """
       Set up pytest global variables.
       """
       pytest.GLOBAL_TEST_VARIABLE = "test global variable"
   ```
   This will instantiate the global variable `GLOBAL_TEST_VARIABLE`, usable for all tests which have access to this `conftest.py` file.

### Use global variables

After instantiating all required global variables in `conftest.py`, you can use them by referencing them with `pytest.<NAME_OF_GLOBVAR>`, i.e.:

```python
import pytest

def test_should_use_global_variable():
    assert pytest.GLOBAL_TEST_VARIABLE == "test global variable"
```

## References

- [PyTest : Namespace (deprecated)](https://docs.pytest.org/en/latest/deprecations.html#pytest-namespace)