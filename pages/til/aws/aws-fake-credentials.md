# AWS: Fake credentials

For some tests, credentials are used at some point. Instead of using actual credentials, it might be best to use fake credentials depending on the use case.

## How to

To mock AWS credentials, you can do something like the following:

**conftest.py**
```python
import pytest

@pytest.fixture(scope="module", autouse=True)
def aws_fake_credentials():
    import os

    os.environ["AWS_SHARED_CREDENTIALS_FILE"] = "path/to/credentials/file"
    os.environ["AWS_DEFAULT_REGION"] = "eu-north-1"
```

By writing it as a PyTest fixture, it can be re-used easily throughout your test suite. The default region is set for enhanced default behavior.

The fake credentials file (**no extension should be used for this file!**) could then be something like this:

**fake_aws_credentials**
```
[fake]
aws_access_key_id = fake_key_id
aws_secret_access_key = fake_key_secret
```

## References

- [Use the AWS_SHARED_CREDENTIALS_FILE environment variable to point to a dummy credentials file](https://stackoverflow.com/a/65017491)