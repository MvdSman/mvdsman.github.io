# Clean Code

While reading _Clean Code: A Handbook of Agile Software Craftsmanship_ by Robert C. Martin, A.K.A. "Uncle Bob", a lot of points made were very relatable. I decided to create these notes to keep a summary of the - for me - most important things to keep in mind.

> I try to link idioms, principles, and other constructs to the [Refactoring](https://refactoring.guru/refactoring/catalog) and [Design Patterns](https://refactoring.guru/design-patterns/catalog) sections of the **Refactoring Guru website**. This is a very handy site for finding patterns, code smells, and more!

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

- **Use wrappers around third-party APIs and consistently use them.** This gives you one location to update upon API changes, instead of having to go through your entire repo.
- **Use "learning tests" to get a feeling of how a new third-party behaves.** This lets you check your understanding of a new package. Write tests which call the API like you expect to use it in your application.
  > "Learning tests" are a great way to **learn** about a new package and **document** your findings (as code) at the same time!
- **Keep "learning tests" in your code base as a functionality validation throughout versions.** Aside from your learning how to use a third-party API, they also allow you to validate the functionality of those same functionalities for newer releases down the road.
- **Use the [Adapter Pattern](https://refactoring.guru/design-patterns/adapter) to test/implement (even non-existing) API interfaces.** This gives you the flexibility to create a testbench environment effortlessly and decouple the transmitter from the receiver.

### Unit Tests

- **Try to keep the Three Laws of TDD *loosely* in mind:**
  1. You may not write production code until you have written a failing unit test.
  2. You may not write more of a unit test than the bare minimum to fail, and not compiling is failing.
  3. You may not write more production code than is minimally required to pass all unit tests.
  > *Do not adhere to these laws too strictly, for they might lead to way too many tests to be manageable.*
- **Test code is just as important as production code.** As said by Robert C. Martin: "*Without tests, every change is a possible bug.*"
- **Write clean tests:**
  - **Readability.**
  - **Build-Operate-Check.**
  - **[Template Method](https://refactoring.guru/design-patterns/template-method).**
  - **Single Concept per Test (Given-When-Then).**
- **Five rules for clean tests (F.I.R.S.T.):**
  1. **Fast** -> People will run them often.
  2. **Independent** -> Test dependency can cause a cascade of failures.
  3. **Repeatable** -> Same results in any environment.
  4. **Self-Validating** -> A boolean output make objectivity and automation possible.
  5. **Timely** -> Writing tests *just before* the production code keeps the code testable.

### Classes

- **Classes should have few responsibilities.**
- **The name of the class should describe the responsibilities.**
  > If the name of the class contains "if", "and", "or", "but", or becomes too complex to describe the responsibilities, you should refactor it into smaller classes!
- **Follow the Single Responsibility Principle (SRP):** a class should have one reason to change.
- **Classes should have few instance variables.**
- **Each class method should manipulate one or more of the instance variables.** The more variables used by a method, the higher the cohesion (which is good).
- **Splitting of a large function often allows for splitting of a large class.**
- **Private method behavior of a subset of class functions hint towards splitting of the class.**
- **Follow the Open-Closed Principle (OCP):** Classes should be open to extension (subclasses), but closed for modification.
- **Use interfaces and abstract classes to isolate the impact of changes ([Facade Design Pattern](https://refactoring.guru/design-patterns/facade)).**
- **Follow the Dependency Inversion Principle (DIP):** classes should depend on abstractions, not on concrete details.
  > For example, a call to a third-party API should not be made directly to that API. Instead, an abstraction interface (class) should be made which is maintanable and testable.

### Systems

- **Separate Constructing a System from Using It:** Prevent the use of the [Lazy Initialization Idiom](https://refactoring.guru/design-patterns/proxy).
- **Separation of Main**: Main will build the objects required for the system, then passes them to the application.
- **Use the [(Abstract) Factory Pattern](https://refactoring.guru/design-patterns/abstract-factory) when the application is responsible for *when* an object gets created.**
- **Use Dependency Injection (DI) to apply Inversion of Control (IoC) to dependency management ([Mediator Design Pattern](https://refactoring.guru/design-patterns/mediator)).**
- **Software systems have scalable architectures - *if* - we maintain the proper separation of concerns.**