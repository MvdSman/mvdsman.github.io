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
   # See https://pre-commit.com for more information
   # See https://pre-commit.com/hooks.html for more hooks
   fail_fast: false # Set to true to have pre-commit stop running hooks after the first failure.
   exclude: ^docs/ # Exclude docs/ folder

   repos:
      # List all files the checks are run on (useful in CI/CD pipelines)
      - repo: meta
         hooks:
            - id: identity
      # Some standard, useful hooks
      - repo: https://github.com/pre-commit/pre-commit-hooks
         rev: v4.2.0
         hooks:
            - id: end-of-file-fixer
            - id: trailing-whitespace
      # Find and remove unused import statements
      - repo: https://github.com/hadialqattan/pycln
         rev: v1.3.3
         hooks:
            - id: pycln
            args: [--all]
      # Sort and categorize your import statements
      - repo: https://github.com/pycqa/isort
         rev: "5.10.1"
         hooks:
            - id: isort
      # Analyzes the code and raises errors where needed
      - repo: https://github.com/pycqa/flake8
         rev: 4.0.1
         hooks:
            - id: flake8
            additional_dependencies:
               - flake8-annotations==2.9.0
               - flake8-broken-line==0.4.0
               - flake8-bugbear==22.4.25
               - flake8-comprehensions==3.10.0
               - flake8-eradicate==1.2.1
               - flake8-simplify==0.19.2
               - flake8-use-fstring==1.3
               - pep8-naming==0.13.0
               - flake8-rst-docstrings==0.2.6
               - darglint==1.8.1
      # Static type checker
      - repo: local # Set to local to make sure it runs in the current venv
         hooks:
            - id: pyright
            name: pyright
            entry: pyright
            language: node
            pass_filenames: true # true; run only on staged files in commit
            types: [python]
            additional_dependencies: ['pyright@1.1.273']
      # Python dependency manager: validate and lock your dependencies
      - repo: https://github.com/python-poetry/poetry
         rev: '1.2.2'  # add version here
         hooks:
            - id: poetry-check
            - id: poetry-lock
            args: ["--check"]
   ```
3. Run pre-commit with this non-default configuration file by using `pre-commit run --config path/to/.usr_pre-commit-config.yaml`

### Further usage

The following are some examples of further usage.

- Run against all files (especially useful after changing your hooks): `pre-commit run --all-files`
- [Advanced features, like running pre-commit on specific stages of git](https://pre-commit.com/#advanced-features): `pre-commit install --hook-type pre-commit --hook-type pre-push`

## References

- [Homepage pre-commit](https://pre-commit.com/)