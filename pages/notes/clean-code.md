# Clean Code

While reading _Clean Code: A Handbook of Agile Software Craftsmanship_ by Robert C. Martin, A.K.A. "Uncle Bob", a lot of points made were very relatable. I decided to create these notes to keep a summary of the - for me - most important things to keep in mind.

## Why clean code

Why would you want code to be clean? For me, it's mostly because:

- Code should be efficient
- Code can be read and enhanced by other people than the author
- Code has a goal which should be clear by reading it

## How to keep code clean

> The following will only be a subset of the entire "ruleset" described in the book. For a full list of the smells and heuristics, see [the table](./clean-code-smells-and-heuristics.md) (the numbering and names match both below and the book).

### Meaningful Names

- **N1: Choose descriptive names.** Logically, this allows for better readability and usability
- **N5: Use long names for long scopes.** Short-lived functions are often doing shorter actions which can be described with less words
- **N6: Avoid encodings.** This will make the functions easier to maintain

### Functions

- **G30: Functions should do one thing.** Single-responsibility functions are easier maintained
- **F1: Too many arguments.** Each extra argument makes a function harder to understand conceptually
- **Prefer exceptions to returning error codes.** Exceptions let you use `try ... catch` constructions to keep the error processing code separated from the happy path code while preventing them from being used as boolean expressions for `if` statements
- **Error handling is one thing.** Error handling is the only thing a function should do: a `try` keyword should always be the first word in a function and no code should be executed after the `catch ... finally` blocks
- **Don't Repeat Yourself (DRY).** Duplication can cause a lot of problems and should always be prevented

### Comments

- **Explain yourself in code.** Prevent writing comments by making function and variable names explain your intent in code
- **Remove commented out code.** Sooner or later, nobody will know what was the purpose of commented out code. CVS tools like Git will make sure you don't lose this code upon actual deletion
- **Keep comments local.** Comments should only contain information regarding directly neighbouring code so it can remain coherent