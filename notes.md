# KOENIG / MOO (2000)

## Preface

"We define abstraction as selective ignorance"

They will present a C++-style approach from the start.

They will present the C++ libraries first then move to personal abstractions.

## Chapter 0

Because << is a left-associative operator, the typical stream stuff parses as

(stream << "something") << endl;

So presumably the result of << is also a std::ostream type.

std::endl is a "manipulator" -- this is a technical term defined by iostream.
This means that it doesn't just write a character
to the stream -- it performs some sort of opaque action, which in this case 
means to terminate the line.

The :: is called the scope operator.  std::cout is a qualified name.

### Exercises

#### Compile and run the `Hello, world` program

Done.

#### What does the following statement do?

3 + 4

Adds 3 and 4 and yield 7 as the result.

#### 0-3

This implementation aligns tabs with the 8-character tab stop.

#### 0-4

Done

#### 0-5

This is *not* a valid program, and why?  I suppose that the braces are
absolutely required for functions.  "The body bof a function must be encosed in
braces even if it is only a single statement.

#### 0-6

This should be a valid program because it just has an evenly numbered of bare
blocks.  And indeed it is.

#### 0-7

I don't believe that this is valid, because comments do not nest as such.

#### 0-8

Although this one is indeed valid

#### 0-9

the shortest valid program would surely just be `int main(){}`
Because `main` is specially allowed to omit return by the spec.

#### 0-10


## Chapter 1

A variable is a place in memory to store an object.  An object has a type.

This form

    std::string name;

is a _definition_.  It defines a local variable.  The variable is destroyed
as soon as the scope enclosing ends.

"Defining a string variable implicltly initializes it, because the standard
library says that every `string` object starts out with a value."

If we don't supply a value, the string starts out containing no characters --
the empty string.

Iostream buffers will be flushed in three scenarios:

1.  they become full
2.  you try to read from standard input
3.  you ask them to be flushed (by writing endl)

std::endl is defined to involve flushing.

seems that the constructor std::string(int, char) will fill a string with said char

When doing an assignment to a std::string from a char*, the implementation will
convert the value automatically. 

You can use `+` to concatenate `string` types (but NOT two string literals!)

`const` -- what does it mean?  It means we are not going to change the value.
If a variable is const, it must be initialized immediately!  You don't have to
use a constant value to initialize a const variable, so it's rather different
from a #define-style constant.

The associativity of operators is not changeable by overloading.

When we use parentheses in a definition, we tell the implementation to call the
constructor.  i.e. to understand `std::string spaces(greeting.size(), ' ')` we
have to know about the `std::string(int, char)` constructor.

When we use `.` we call a _member function_, this being the C++ word for method.

This `' '` is a character literal.  It's a single char and I think that it has
to be ASCII or at least 8-bit.

When we know that `std::string(int n,char c)` will duplicate the character `c`
times `n` -- filling up the string, then we can understand this definition.

This form:

    std::string name;

is called "default initialization" and is weird.
http://en.cppreference.com/w/cpp/language/default_initialization

These forms are clearly distinguished


    std::string hello = "foo";       // explicit initialization
    std::string stars(100, '*');     // constructor initialization
    std::string name;                // default type-dependent initialization

### Exercises

1-0 -- Done.
1-1

This should be valid.

    const std::string hello = "Hello";

I think that this is also valid, because the constness of the initializer 
doesn't affect variable constness.  Actually the real point here is the 
associativity of the + operator affecting the parse order, because you can't
concatenate two char* literals.

    const std::string message = hello + ", world" + "!";

1-2

This should be valid.

    const std::string exclam = "!";

This will fail though because it will parse as ("hello" + "world") which is
an invalid expression.

    const std::string message = "hello" + ", world" + exclam;

But this would work

    const std::string message = "hello" + (", world" + exclam);

1-3

Without running it I'd say that yes it's fine and it prints "a string\nanother
string\n".   Because the two locals are local to their relative blocks so they
don't shadow each other.  And that was correct.

1-4

I misread this, the first scope hasn't been closed.  Yeah, it's valid and fine.
The ; doesn't affect it.

1-5

This won't work because x has been destroyed at the time we try to print it.
`error: 'x' was not declared in this scope`

Rewrite it to be valid?  Just move the second cout into the inner scope.

1-6

My prediction of running the program:  It will read samuel beckett into the string name.

And so it will print

    Hello, Samuel Beckett
    And what is yours?

Don't really get this question.  Something to do with buffers flushing?
I can't see how it could have any other behaviour.

It does actually read a single word Samuel into `name`.  How terrible
How could this happen?

"Executing `std::cin >> v` discards andy shitespace characters in the standard
input stream, then reads from the standard input into variable v"

???  That still doesn't explain this behaviour.

`std::cin` causes the buffer to flush the word Samuel only to the variable!
Everything's read into cin's internal buffer.

Basically cin reads until whitespace separation which is nuts.

## CHAPTER 2: LOOPING & COUNTING

We rewrite the program to try to generate the lines based on an algorithm of some
kind.  It's not 100% clear what the spec is at the start.

See source `loop_greeting.cc`

To justify the existence of the `++` operator, they say

"the idea of transforming a value into its immediate successor, in contrast with
computing an arbitrary value, is so fundamental to abstract data structures that
it deserves a special notation for that reason alone".

They introduce the idea of a loop invariant.  Quoth:

    "[A loop invariant is] a property that we assert will be true about a while 
    each time it is about to test its condition.  We choose an invariant that
    we can use to convince ourselves that the program behaves as we intend, and
    we write the pgoram so as to make the invariant true at the proper times.
    Although the invariant is not part of the program text, it is a valuable
    intellectual tool for designing programs.  Every useful 'while' statement
    that we can imagine has a loop invariant associated with it.  Stating the
    invariant in a comment can make a 'while' much easier to understand.

    ...
    
    The general idea is to find an invariant that states a relevant property of the
    variables that the loop involves (we have written `r` rows), and to use the
    condition to ensure that when the loop completes, those variables will have
    useful values (r == rows).  The loop body's job is then to manipulate the 
    relevant variables so as to arrange for the condition to be false eventually,
    while maintaining the truth of the invariant.

They note that std::string::size_type is an unsigned integer type.

The relational operators have lower precedence than the arithmetic operators.


