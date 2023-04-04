# Pre-commit: how to configure and use

Pre-commit hooks allow you to run certain checks prior to committing your code to your git repository. This can range from whitespace removal to validating your dependencies.
Although pre-commit itself runs in Python, it can be used for any programming language.

## How To

### Configure pre-commit

Assuming you installed pre-commit as described in the pre-commit docs, you can configure your pre-commit hooks as follows:

1. If there's no pre-existing `.pre-commit-config.yaml` file in your repository, you can create a sample file using `pre-commit sample-config`
2. To automatically run pre-commit when calling `git commit`, run `pre-commit install`

### Use a non-default pre-commit file

If you need to run pre-commit using a different configuration file than your default configuration in `.pre-commit-config.yaml`:

1. Create a new, differently named pre-commit configuration file, i.e. `.usr_pre-commit-config.yaml`
2. An example of a fleshed out configuration file which includes formatting checks and dependency file checks
   ```yaml
   ...
   ```
3. Run pre-commit with this non-default configuration file by using `pre-commit run --config path/to/.usr_pre-commit-config.yaml`

### Further usage

The following are some examples of further usage.

- Run against all files (especially useful after changing your hooks): `pre-commit run --all-files`
- [Advanced features, like running pre-commit on specific stages of git](https://pre-commit.com/#advanced-features): `pre-commit install --hook-type pre-commit --hook-type pre-push`

## References

- [Homepage pre-commit](https://pre-commit.com/)