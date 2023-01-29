# AWS Lambda Powertools: Structured Logging Guidelines

The [AWS Lambda Powertools](https://awslabs.github.io/aws-lambda-powertools-python/) package is a very powerful extension for adopting best practices such as tracing, structured logging, custom metrics, idempotency, batching, and more.

After experimenting with structured logging (JSON format as a result), I ended up with the following usage tips for optimal usage.

## How to

The following tips are not necessarily required, but serve as a few guidelines on how to use structured logging.

- **You should always try to set a value for the `service` parameter inside the logging handler initialization.** This allows someone to filter for logs of specific services while using the CloudWatch Insights log queries. This would ideally be on the level of stacks or higher, depending on how you set up your services.
- **Keep in mind that you are not limited to a single `message` parameter inside the logger for passing down information anymore.** Utilize the ability to add additional key-value pairs for supplying information in an actual structured manner. This facilitates automated field extraction and easier querying without needing to parse `message` for information, i.e.:
  ```python
  # Bad usage of structured logging
  logger.warning(f"Failed to fetch data from {data_container}! Exception: {exception}")
  # Results in CW Logs:
  # {
  #   ...,
  #   "message":"Failed to fetch data from example_data_container! Exception: SomeExceptionInfoHere",
  #   ...
  # }

  # Good usage of structured logging
  logger.warning(
    message="Failed to fetch data!",
    extra={
      "data_container": data_container,
      "exception": exception,
    },
  )
  # Results in CW Logs:
  # {
  #   ...,
  #   "message":"Failed to fetch data!",
  #   "data_container": "example_data_container",
  #   "exception": "SomeExceptionInfoHere",
  #   ...
  # }
  ```

  > In short: keep `message` as a way to inform someone that ***something is done or observed*** and use the `extra` parameter to inform someone of ***what has happened or has been observed***.
- **You can add entire dictionaries and lists as values to a key in the `extra` field**: this allows for easy logging of gathered information throughout your Lambda execution.
- **When adding dictionaries to the extra field, keep in mind that nested dictionaries will be unpacked.** Children will be separated into separate key-value pairs with a dot (`.`) as separator, i.e.:
  ```python
  dict_var = {
    "parent": {
      "child1": {
        "subchild1": 1,
        "subchild2": 2,
      },
      "child2": {
        "subchild1": 3,
      },
    },
  }
  logger.info(
    message="Added dict to extra",
    extra={
      "dict_var": dict_var,
    },
  )
  # Results in CW Logs:
  # {
  #   ...,
  #   "message":"Added dict to extra",
  #   "dict_var.parent.child1.subchild1": 1,
  #   "dict_var.parent.child1.subchild2": 2,
  #   "dict_var.parent.child2.subchild1": 3,
  #   ...
  # }
  ```
- **Make sure you provide your information in the correct structure** so you can easily parse or query data. Dictionaries might require more advanced querying/parsing depending on the data.


## References