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
- **Prefer exceptions to returning error codes.** Exceptions let you use `try-catch` constructions to keep the error processing code separated from the happy path code while preventing them from being used as boolean expressions for `if` statements
- **Error handling is one thing.** Error handling is the only thing a function should do: a `try` keyword should always be the first word in a function and no code should be executed after the `catch-finally` blocks
- **Don't Repeat Yourself (DRY).** Duplication can cause a lot of problems and should always be prevented

### Comments

- **Explain yourself in code.** Prevent writing comments by making function and variable names explain your intent in code
- **Remove commented out code.** Sooner or later, nobody will know what was the purpose of commented out code. CVS tools like Git will make sure you don't lose this code upon actual deletion
- **Keep comments local.** Comments should only contain information regarding directly neighbouring code so it can remain coherent

### Formatting

- **The Newspaper Metaphor:** This makes code more comprehensible to read
  1. You read your code vertically
  2. The name of the function should be clear enough to know if you are in the right module
  3. The top should exist out of high-level concepts and algorithms
  4. Details should increase as we move downward
  5. A newspaper is composed of many articles, such as a module should be composed of multiple functions, making it usable
- **G10: Vertical sparation.** Related concepts should be kept vertically close to each other and the calling function should be above the callee

### Objects and Data Structures

- **Stick to the Law of Demeter whenever possible.** A method should not call the methods on objects that are returned by any of the allowed functions (talk to friends, not to strangers)
  > The Law of Demeter: *A module should not know about the innards of the objects it manipulates.*

### Error Handling

- **Write your `Try-Catch-Finally` Statement First.** This lets you define a scope in which your code runs
- **Try to write tests that force exceptions, then the required logic.** This lets you set up and maintain the transition scope of the `try` block
- **Combine error handling with TDD:**
  1. Create a unit test that forces an exception upon error and checks for it
  2. Create a (failing) function stub that is called by the unit test but does not return the expected exception
  3. Implement basic logic that returns the expected exception upon error using a `try-catch` statement
  4. Upon passing the unit test, refactor where possible/required using TDD
- **Don't Return Null.** Returning Null will require more validation code instead of simply returning for example an empty list which you iterate through afterwards.
  > If a 3rd party API returns Null, consider wrapping the Null-returning methods in a method that either throws an exception or returns a special case object

### Boundaries
