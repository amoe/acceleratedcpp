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

To justify the existence of the `++` (autoincrement) operator, they say

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

They teach `for` as a shortening of the `while` loop.  and say that it generates
a range, the final value being the _off-the-end value_ for the range.  A half-open
range.  [begin, off-the-end)

That is, `r` takes on the values in [0, rows)

Note that in c++ you can inline functions.  People avoid Extract Method in C++
sometimes because function calls are expensive but you may just inline them.

A range of the form [m, n] has n - m elements by definition.
Therefore [n, n) is an empty range.

The reason that the authors prefer to use `!=` in while conditions is so that
we have extra information about the loop variable at the end.  But if it only
exists in the scope of a for loop, then that doesn't apply.  So there is perhaps
a good reason to use != conditions in while loops, but perhaps not for loops.

The usual arithmetic operations normally attempt to preserve precision.  Smaller
types get converted into bigger types.

## EXERCISES

2-0: Done

2-1: Done by setting all padding values to 0.

2-2: Done by setting the values of `padding_left` and `padding_right`

2-3: Done by introducing a cin which can read an int.  Then just assign all
padding values from this int.

2-4  This one's tricky because you can't just always print the greeting length.
You need to exactly hit the loop condition, otherwise you're going to end up
printing more spaces than you need which will lead to overflowing the box
with spaces.  Note that there's probably a way to print the corect amount of
padding as well.  But we skip the greeting row to avoid this decision.

2-5  Nice exercise but I'm not going to do it.

2-6  It should print the numbers 0 to 9.  Actually it prints 1 to 10, of course.

2-7  
    for (int i = 10; i >= -5; i--) {
        std::cout << i << std::endl;
    }

2-8  A tiny bit tricky because you have to make sure you intialize product to 1.

    int product = 1;

    for (int i = 2; i < 10; i++) {
        product *= i;

    }

    std::cout << product << std::endl;

2-9
Done, simple

2-10

The first example creates an alias cout in side the block beginning while(k!=n)
But the alias only exists in the scope of that block.  So std::is still required
here.  It's useful to see that `using` is a regular scoped statement.

























## CH3 - Working with batches of data

SO I presume that this will be about vectors.

New concepts:

* cin can be chained to read multiple lines in a single statement.
* cin does input formatting to allow reading doubles.
* cin will yield a false status on EOF, allowing it to be used in loops
* the iomanip header -- this gives several things.
    * streamsize type
    * the "precision()" function which I guess sets a precision like printf
    * it's left-shifted onto the stream just like real output
    * cout << setprecision(3)
    * This modifies the stream property and then you have to reset it.
    * You can save away the previous precision by calling cout.precision()
* uninitialized variables contain rubbish!  they will crash the program if used
* while (cin >> thisGrade) works because: 

"the istream class provides a conversion that can be used to convert cin into a
value that can be used in a condition".  Presumably it overloads a boolean-coercion
operator and returns the eof value.

Actually it returns a success value, there are several ways in which it can fail:
* end of file
* input incompatible with type
* hardware failure (broken pipe, etc)

The loop invariant contains two clauses which indirectly affect each other.

Now we modify it to use the median.

What does it mean to be a template class?  We don't know but we know that we can
separate what it means to be a vector from the particular type of the object
that the vector holds.  We specify the type of the contents inside angle
brackets.

They explain std::vector, which .. works as we expect.

Apparently we also have to check that the size is zero.

They introduce this gnarly statement:

    typedef vector<double>::size_type vec_sz;

This defines a type abbreviation.  In general you should use size_type for all
container sizes.

But surely `vec_sz` is a dubious name for this because it is contingent on the
vector being of type double?

Typedef names are *scoped* so don't worry about them.

They introduce sort, and also the mysterious .begin() and .end().

.begin() describes the first element, .end() denotes *one past* the last element,
see ch8

sort works in place, it mutates the array.

Integer division -- The result is truncated towards zero.

size_type is unsigned therefore it's reasonable to check size == 0.  I guess
we kind of ignore this as programmers.

When signed integers and unsigned integers combine in an expression, ordinary 
integers are converted to unsigned.  That is

The result of 
    homework.size() - 100

is unsigned, therefore it's 0 at the minimum.  This is actually somewhat cool.

The high level performance goals of are specified:

* Appending to std::vector is O(n) although surely it can be O(1)?
* Sort is O(log(n))

The max() function is defined in <algorithm>.
<ios> defines the `streamsize` type which is an opaque type used by precision().

### Exercises

3-0 -- Done.

3-1 -- No idea how to do this.  

Well yeah, imagine that we have read the values

1, 2, 4, 8

Now imagine that we discard the value 4

If we then read another value 16, the median should be 4.

But we discarded it, therefore it will incorrectly be seen as (2+8)/2 = 5.

3-2

This exercise is weird, I couldn't do it properly.

3-3 

Done with a weird solution

3-4

Done with no problems

3-5

I'm too lazy to do this one, it's mostly boring book keeping.

3-6

Find what does division by zero do.
It makes a floating point exception and crashes the program.  It also generates
a message in dmesg `trap divide error`!  It's shocking that this doesn't happen
literally all the time.  The adaptation is pretty simple, you just change it
to check if count == 0 after the loop and bail out if this is the case.























































## Chapter 4 -- Organizing programs


"when we call grade(...), the grade function's parameters are initialized to
copies of the arguments' values, and do not refer directly to the arguments
themselves.  This behaviour is often called 'call by value'."

New items:

* std::domain_error -- when arguments are wrong, basically equivalent to some
java preconditions (stdexcept)
* the fact that vector<double> in an arguments list will copy the vector
* const vector<double>& will "pass by const reference", a fast and immutable pass
* overloading by function argument
* "lvalue" -- a non-const reference argument can only be filled by a lvalue, 
which is a nontemporary object.  You can also return references which can then
be passed as lvalues.  That's pretty cool.
* clear() method resets the error flag in an istream
* `try` keyword to catch exceptions -- only type supported for now?
* 

references are another name for an item.  Once a reference or an object X has
constness, you can't make a nonconst reference to that object.  eg this should
fail.

const int x = 42;
int& y = x;  // should fail

    error: binding reference of type 'int&' to 'const int' discards qualifiers


How do we indicate two return values at once?  Normally through custom data
structures.

But, we can also use reference passing to fill a value of the caller.  (This
can't really be done in other langs.)


They suggest clearing the caller's vector which is really weird.

The problem with reading grades is that you might also encounter a situation
where you couldn't read a double, in which case -- ? 
The iostream library will mark the input stream as being in "failure state" which 
is  pretty stupid.

So we're going to have to clear the failure state on the stream and ignore errors.


"It is porobably not worht the bother to use const referneces for simple primitives"

But it is worth it for strings and vecctors.

emptyvec() is an example of an expr that is not an lvalue.


so we introduce a data structure for per student datum

question: Why pass input stream by reference?

they leave open the question of how to decide a comparator for a given sort

this is determined by using the < (less-than) operator

so basically you just overload the < operator to implement comparable

More new items:
* struct declarations
* sorting custom data sttructues
* what() method in exceptions
* std::max from <algorithm>

Both arguments to max must have the same type, *exactly*, that's 

Sort takes a third argument that's a predicate.

This returns true if x is less than y.

 So we write a custom comparator.


They introduce separate compilation.

System headers are ones included through <> but they don't actually need to be
implemented as header files.

In the header file you need fto ... declare the function.

They use std:: prefix explicitly in the header, why?

"Header files should declare only the names that are necessary"
so by adding `using` to headers, you're leaking names into the client's namespace.

Hence: HEADER FILES SHOULD NEVER USE `using`.

they introduce include guards.

they also don't give names to the argument parameters in header files which is.
uh.
