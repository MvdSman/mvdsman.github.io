# PyTest: Use fixtures

PyTest fixtures provide a fixed baseline so that tests execute reliably and produce consistent, repeatable results. Initialization may setup services, state, or other operating environments.

## How To

> Defined fixtures don't have to be imported by the file containing the tests: they only have to be present in one of the higher-level `conftest.py` files. This makes them ideal for controlling the test suite.

### Fixture for separating the preparation from the test

You can use a fixture to control the way tests run while keeping the tests themselves concise and focused.

Example:

**conftest.py**
```python
import logging

@pytest.fixture(scope="session")
def setup_logger():
    logging.basicConfig()
    logger = logging.getLogger("test_logger").setLevel(logging.INFO)
    return logger
```

**test_file.py**
```python
import pytest

def test_logger(setup_logger):
    test_logger = setup_logger
    test_logger.info("This message is sent by the test logger set up outside this test")
    ...
```

### Fixture for setup and teardown

Fixtures can also be used to setup a test environment and then tear it down afterwards. This is especially important when working with servers or ETL jobs.

Example:

**conftest.py**
```python
import logging
from custom_server import SomeServerController

@pytest.fixture()
def setup_then_teardown():
    # Set up the server
    server = SomeServerController()
    server.start()

    # Run a test function
    yield

    # Tear down the server
    server.stop()
```

This fixture could then be called by a test function to allow that test function to interact with this server.

## References
- [PyTest Docs: Fixtures](https://docs.pytest.org/en/6.2.x/fixture.html)