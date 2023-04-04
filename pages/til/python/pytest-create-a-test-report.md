# PyTest: Create a test report

## How To

To create a PyTest test report, you need to export it to JUnit XML file and then have a tool which can render that JUnit XML file. I chose for a plugin called [junit2html](https://gitlab.com/inorton/junit2html) to render the XML file to an HTML file.

### Create a JUnit XML report file

Run PyTest from the target project venv (i.e. using Poetry): `poetry run pytest -v -s --junit-xml=report.xml | tee log_for_testers.log`

> This command also export the terminal log to a log-file for further debugging. Note that the `-v -s` parameters are optional.

### Render the HTML report

1. Make sure that the `junit2html` package is installed (as dev dependency)
2. Run the renderer: `python -m junit2htmlreport path/to/report/report.xml`
3. Open te HTML report, which is created in the target folder where the report.xml also resides

## References

- [PyTest : Creating JUnitXML format files](https://docs.pytest.org/en/latest/how-to/output.html#creating-junitxml-format-files)