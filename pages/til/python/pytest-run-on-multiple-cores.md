# PyTest: Run on multiple cores

## How To

To run PyTest on multiple CPU cores, perform the following steps:

1. Install the pytest plugin `pytest-xdist`
2. Call pytest using the plugin's additional parameters, default usage: `pytest -n auto`. With this call, PyTest will spawn a number of workers processes equal to the number of available CPUs, and distribute the tests randomly across them.

For a more refined distribution of the tests, see some of the following options:

- Distribute tests amongst cores grouped by module for _test functions_ and by class for _test methods_: `pytest -n auto --dist loadscope`
- Distribute tests amongst cores grouped by their containing file: `pytest -n auto --dist loadfile`

## References

- [PyTest xdist](https://github.com/pytest-dev/pytest-xdist)