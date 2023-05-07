# AWS: Use moto server

During testing, it's something required to test the responses of the AWS services. This could be done using a local moto server, as described below.

## How to

First off, you'll need to install the [`moto`](https://github.com/getmoto/moto) package with a few dependencies to get the server host working correctly. Moto is a library that allows your tests to easily mock out AWS Services.

To install the correct dependencies, use the following:
```sh
pip install moto[server]
```



**conftest.py**
```python
import pytest

@pytest.fixture()
def moto_server_handler():
    from moto.server import ThreadedMotoServer

    local_server = ThreadedMotoServer()
    server.start()

    yield  # Run any test logic

    server.stop()
```

By writing it as a PyTest fixture, it can be re-used easily throughout your test suite.

An example on how to use this handler during a test:

**test_server.py**
```python
import pytest
import boto3

def test_should_use_server(moto_server_handler):
    session = boto3.Session()
    logs_client = session.client(
        service_name="s3",
        region_name="eu-north-1",
        endpoint_url="http://localhost:5000",
    )
    ...
```

## References

- [Moto - Server mode](https://docs.getmoto.org/en/latest/docs/server_mode.html)