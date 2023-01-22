# Clean Code: Smells and Heuristics

The following table is based on [Nicole Carpenter's cheat-sheet](http://nicolecarpenter.github.io/2016/03/29/clean-code-chapter-17-smells-and-heuristics.html) as a starting point. I suggest to get a copy of the actual book _Clean Code: A Handbook of Agile Software Craftsmanship_ by Robert C. Martin if you want to read more about it, including code examples!

## Comments

Code Smell / Heuristic | Description | Refactoring
--- | --- | ---
Inappropriate information 				| Record keeping or other metadata in source code | Keep this type of comment in other systems
Obsolete comment 						| Old, irrelevant or incorrect comment 			| Delete it, avoid using comments that will become obsolete (or at all)
Redundant comment 						| Comment describes something that would adequately describe itself | Omit redundant comments, refactor code to be clear
Poorly written comment 					| Comment is not clear about its purpose for writing | Write understandable comments, brief and to the point
Commented out code 						| Chunks of code not in use but lingering in the source code | Delete it, it will become obsolete if left long enough

## Environment

Code Smell / Heuristic | Description | Refactoring
--- | --- | ---
Build requires more than one step 		| Requiring multiple steps to build 			| Combine setup to a single command
Tests require more than one step 		| Requiring multiple calls to run all tests 	| Reorganize files to call back to a spec runner

## Functions

Code Smell / Heuristic | Description | Refactoring
--- | --- | ---
Too many arguments 						| Three or more arguments on a function 		| Try for zero arguments, add only if necessary
Output arguments 						| Function changes something with an output* 	| If the function must change the state of something, have it change the state of its owning object
Flag arguments 							| Boolean arguments hint that the function does more than one thing | Avoid, break up receiving function to handle two cases
Dead function 							| Methods that are not called 					| Delete and don't write until they are needed

## General

Code Smell / Heuristic | Description | Refactoring
--- | --- | ---
Multiple languages in one source file 	| Mixing multiple languages in one file 		| Separate languages where possible and practical into their own source file
Obvious behavior is unimplemented 		| Code behaves counter-intuitively 				| Descriptive naming that communicates the intent of the code
Incorrect behavior at the boundaries 	| Code behaves counter-intuitively for edge cases | Test all cases, look for every boundary condition
Overridden safeties 					| Turning off warning and exceptions to get the code to build | Deal with debugging as it comes up, only override when last resort
Duplication 							| Identical (or closely similar) code appearing over and over | Replace with better methods, abstractions and polymorphism*
Code at wrong level of abstraction 		| High and low level abstractions appear together | Separate lower level concepts into derivatives and higher level concepts in the base class
Base classes depending on their derivatives | Base classes mentioning derivatives 		| Base classes should generally not know about their derivatives
Too much information 					| Wide and deep interfaces that require multiple gestures to get things done | Limit exposure at interfaces, with fewer methods, variables and instance variables
Dead code 								| Code that is not executed 					| Delete dead code if it serves no purpose
Vertical Separation 					| Large vertical scope between declaration and use | Declare variables and functions close to where they are used
Inconsistency 							| Not following a convention 					| Pick a way to do and name things and stick to it
Clutter 								| Anything that is not used or not needed in the code | Keep code base clean and to the point
Artifact coupling 						| Coupling between two modules that serves no direct purpose | Take time to figure out where functions, constants and variables belong
Feature envy 							| Using accessors and mutators of some other object to manipulate the data within that object | Try to have class methods only interact with variables and functions of classes they belong to
Selector arguments						| Passing code to a function to select the behavior | Split large functions into smaller functions
Obscured intent							| Code that is hard to read, intent not clear	| Make intent of code visible to reader
Misplaced responsibility				| Code appears in the wrong class or interfaces | Place code where reader would naturally expect it to be
Inappropriate static					| Static function when should be nonstatic		| Only make a function static if there is no chance it will need to behave polymorphically
Use explanatory variables				| Large calculations with wide span 			| Break calculations up into intermediate values in variables with meaningful names
Function names should say what they do 	| You can't tell from the call what the function does | Find better names that express intent
Understand the algorithm				| Code is thrown together that "works"			| Refactor to a clean and expressive function that is obvious how it works
Make logical dependencies physical		| Dependent modules make assumptions about the module it depends upon | Dependent modules should explicitly ask other module for all information it depends upon
Prefer polymorphism to If/Else or Switch/Case | Use of brute force switch statements	| Consider polymorphism where you would consider a switch statement
Follow standard conventions				| Not following normal convention, team-specific styles | Follow a coding standard based on common industry norms
Replace magic numbers with named constants | Leaving numbers in code that represent a specific idea | Change "magic numbers" to constants
Be precise								| Ambiguities and imprecision in code 			| Make decisions precisely, knowing why the decision was made and how to handle exceptions
Structure over convention 				| Poor design decisions							| Use structures that force compliance
Encapsulate conditionals				| Context is difficult to understand in conditional | Extract functions that explain the intent of the conditional
Avoid negative conditionals				| Conditionals expressed as negatives			| Change methods to return the positive rather than negating a negative
Functions should do one thing 			| Function with multiple sections that perform a series of operations | Convert large function into several small functions
Hidden temporal couplings				| Order is not obvious for temporal coupling 	| Add extra syntatic complexity to make the temporal coupling explicit
Don't be arbitraty						| Unorganized code, unclear intent				| Have a reason for the structure and make sure the structure communicates the reason
Encapsulate boundary conditions 		| Boundary conditions leak all over the code 	| Put the processing for boundary conditions in one place
Functions should descend only one level of abstraction | Mixing levels of abstraction 	| Function statements should be at the same level of abstraction, one level below the operation described by the name of the function
Keep configurable data at high levels	| Constants expected at high level of abstraction buried in low-level function | Expose high level constants as arguments to low level function called from high level functions
Avoid transitive navigation 			| Single modules know too much about collaborators | Make sure modules only know about immediate collaborators and not the navigation map of the whole system

## Names

Code Smell / Heuristic | Description | Refactoring
--- | --- | ---
Choose descriptive names 				| Names don't describe intent					| Make sure name communicates what the purpose of the function or variable is
Choose names at the appropriate level of abstraction | Names communicate implementation | Name things to reflect the level of abstraction of the class or function you are working in
Use standard nomenclature where possible | Names are not relevant to the project		| Base names on existing convention or usage
Unambiguous names 						| Name does not communicate what the function or variable does/is | Choose names that make intent clear and unambiguous
Use long names for long scopes			| Short names that apear over wider scope 		| Reserve single letter variables for small, local scopes
Avoid encodings							| Scope or type information encoded into names 	| Keep names free of pollution
Names should describe side-effects 		| Side effects hidden 							| Names should describe everything that a function, variable, or class is or does

## Tests

Code Smell / Heuristic | Description | Refactoring
--- | --- | ---
Insufficient tests 						| Some conditions remain unexplored by tests or calculations unvalidated | Test everything that could possibly break
Use a coverage tool						| Relying on manual tests 						| Use coverage tool with visual indication of coverage
Don't skip trivial tests 				| Not testing small aspects of the code 		| Test everything!
An ignored test is a question about ambiguity | Not adding a test because something is not understood | Add commented out or ignored test to question the requirements
Test boundary conditions 				| Not considering all edge cases 				| Consider all boundaries and test them
Exhaustively test near bugs 			| Not using extra cauting with testing when a bug is found | Test functions that have bugs very exhaustively
Patterns of failure are revealing 		| Incomplete test cases poorly organized		| Create complete test cases to diagnose problems
Tests should be fast					| Slow running tests that won't get run 		| Keep tests running quickly by whatever means necessary (situations will vary)