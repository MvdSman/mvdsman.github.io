# PyTest: Calculate code coverage

## How To

To calculate code coverage in Python, you can use several tools. I chose for a plugin called [pytest-cov](https://pypi.org/project/pytest-cov/) to keep everything running inside the context of [PyTest](https://docs.pytest.org/en/7.2.x/).

### Install pytest-cov

You can install pytest-cov using either pip or poetry using:
- `pip install pytest-cov`
- `poetry add --group dev pytest-cov`

### Get a coverage report in the terminal

To get a coverage report in the terminal, you can run the following command, assuming you have a poetry shell active:

```ps
poetry run pytest --cov
```

This will result in something like the following table:

```ps
Name                        Stmts   Miss  Cover
-----------------------------------------------
hashtable_tdd\__init__.py       1      0   100%
hashtable_tdd\main.py          26      0   100%
tests\__init__.py               0      0   100%
tests\test_hashtable.py        59      1    98%
-----------------------------------------------
TOTAL                          86      1    99%
```

### Generate a HTML coverage report

To generate this report in HTML, including a more detailed per-file inspection page, run the following command in a active poetry shell:

```ps
poetry run pytest --cov --cov-report=html
```

This will create a folder called `html-cov` in the execution location which will contain the HTML report:

![PyTest coverage report index page]({{ site.urlimg }}pytest-coverage-report-index.png)

![PyTest coverage report detail page]({{ site.urlimg }}pytest-coverage-report-detail.png)

## References

- [Py.Test : Reporting and HTML output](https://stackoverflow.com/questions/17557813/py-test-reporting-and-html-output)