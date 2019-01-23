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

A zero member struct is legal.

Overloading can distinguish between a regular reference and a const reference.

More new items:

* inline functions requests the function to be inline, but should be avoided
  nowadays.
* Several classes from stdexcept:

logic-error, range_error, length-error, domain-error, out-of-range, overflow-error
invalid-argument, runtime-error, underflow-error

s1 < s2 compares using dictionary ordering

s.width(n) on a stream will pad on the left to a given width.  Call width(0)
to reset the width.  Madness.

setw(n) is the I/O manipulator version of the above.  s << setw(10)

## Chapter 5 -- Iterators

New things:

They show modifying the reference of a caller's vector by replacing it with
a totally new reference, and recommend an odd strategy of creating two outputs
from a function using references.

An in place approach would be possible but non feasible because removing items
from vectors is obscenely slow.  i.e. it's O(n^2)

We choose to address the perf / memory issue by just using a more appropriate
data structure, although I can't really imagine what such a structure could be.

The use of erase() function on a vector to remove elements.  And also the use
of begin() when using an offset -- this is a version that's not actually using
an index -- erase() takes a special type of arg -- and that type of arg is
an iterator.

They point out that loops using explicit indices are rather unclear because they
don't restrict the possible range of interpretations.  You're only looping
sequentially, but the presence of `i` means that you need to understand the whole
loop body to ensure that access is not in fact non-sequential -- random, etc.
This is an argument for `foreach` loops, `map`, etc.

By using restricted structures, you can write code that runs more efficiently
because the library can use implementations that have optimization properties
that depend on those restrictions.  Like, imagine that you can use LinkedList to
do a map() operation.  Iterators are for this.

An iterator is an object that identifies both a container and a current-element.
It provides operations for moving between other elements in various ways.

You rewrite an index loop to iterator as such:

for (vector<StudentInfo>::const_iterator iter = students.begin(); iter != students.end(); iter++)

Note the new type `const_iterator`, we'd probably want a type alias for this.
Or you can just use auto, I'd guess.  That's one time when auto is much nicer.

To get the actual item, you need to dereference the iterator.  This is kind 
of crazy.

`(*iter).name` will access the field `name`.

I don't know if this is done by operator overloading, or somehow an iterator
simply is a pointer?
Without const_iterator you can modify the content using *foo = bar.

.begin() returns an iterator that gets automatically converted to `const_iterator`.
This conversion is done automagically, but it's one way -- obviously you can't
go from const to non-const.

++iter is an overloaded operation.  

But you can also write `foo->field` instead of `(*foo).field`.  

`students.begin() + i` only works because of some overloading, so this will
return an iterator also.

Oh right, it's more that pointers in C-language were already actually iterators,
inasmuch as they support ++ and `*` operations!  So the iterator system is a
generalization of pointer arithmetic.

We say that the run time of erase() is quadratic, O(n^2).  The `list` type is
optimized for the access pattern of inserting and deleting midway through the
container, unlike `vector`.  "If the container grows and shrinks primarily from
the end, a vector will outperform a list".  So if you're only using push_back,
then you can be fairly certain a vector is the right choice.  Lists don't support
index-based access.

My own thought: it's kind of slightly odd that Lisp is based on linked-lists, when
inserting + deleting from the middle lists is a more "imperative" styled operation
than inserting or deleting at the back.

"The `list` type is a template, so we must say what kind of object the `list`
holds by naming that type inside angle brackets, just as we do when we define
a vector."

Never save the value of `container.end()`!

We can't use sort() to sort a `list` because, rather logically, it requires
random access.  Perhaps we could use a different sorting algorithm.  Indeed,
list provides its own method list::sort.  students.sort(compare);  I wonder
what algorithm this one uses.

The larger point of the example is that the choice of data structure can have
a profound impact on performance.  They use a concrete example to show that
the run time of the vector-based example can stretch up to ten minutes (!)

### 5.6 -- strings.

We can think of strings as containers much like vectors.  They support random
access and provide iterators.
We implement a split function using an iteration approach with two loop counters
`i` and `j`.  I'm not a big fan of the algorithm they present here.

They introduce the `getline` function which will read an entire line into a string
which is passed by reference.

### 5.8 -- putting strings together

We want to write a program that contains the entire 'framed' output, like chapter
2, in a single string.

Write all the words stored in a vector and surround them with a border.

There's no vector concatenation operation in C++, so we have to do it ourself
with an operation `vcat`

A question:

We remove the constness of the top reference by copying it and then add to it??

vector<string> ret = top;

When you assign a const rvalue to non-const rvalue, the data gets copied
implicitly.  ret.push_back();

They define an 'hcat' algorthm for horizontal concatenation of "word pictures"
which is relatively unremarkable -- except that it demonstrates when you can
keep track of two indices, but probably still not go to quadratic time.  I'd
say that this is still O(n) algorithm.


## CHAPTER 6 - USING LIBRARY ALGORITHMS


The equivalent of `extend` in Python is the following:

    ret.insert(ret.end(), bottom.begin(), bottom.end());

Assuming that they are both vectors.


They want to invert this description so that you're basically copying a source,
defined by a start and end iterator position, to an arbitrary sink:

    copy(bottom.begin(), bottom.end(), back_inserter(ret));

This is pseudo code, but the expression `back_inserter(ret)` is assumed to
return some sort of sink that ends up in `ret`.  They call this an _iterator
adaptor_.  (Actually it's not pseudocode.)

So we're now getting to generic, which is pretty sweet.  In this case, `copy`
is a generic algorithm.  And the signature looks as such:

    copy(begin, end, out);

They briefly give the postfix/prefix increment operators.

`back_inserter()` is an actual function from `<iterator>` header.

So the take-away here is that an iterator can also be a "destination" or a sink.
I guess that this is implemented by an overload on the assignment.  Oy vey
So you can imagine an equivalent for back_inserter that is actually going
to overwrite elements that already exist.  Or perhaps the `back_inserter` is
actually going to do an arbitrary tranformation on the element before adding it
to the vector.

### Another way to split

Find several things there, that now we do actually have to include algorithm,
I think.

You can't just pass std::isspace directly to find_if, because it's overloaded
so that it can also deal with `wchar_t`.
You can't easily pass overloaded functions as arguments to template functions,
because the type isn't known.
Hence we have to make these wrappers that uncomplicatedly take `char`.

One new thing is the string constructor that takes two iterators and constructs
the string between those two iterators.

### Palindromes

Fairly uncontroversial, this is a neat and clever function.

### URL detection

Note their use of "static const string"

This is a fairly cool algorithm that demonstrates scanning iterators using
`find_if` and a predicate, a nearly-functional style.

Some stuff is incorrigibly ugly though, for instance, see `not_url_char()`

### Comparing grading schemes

Note the use of the `.empty()` member function on vectors which predictably
returns true if something is empty.

They'll pass functions to the writing procedures to parameterize them.

They introduce map() -- under the name transform()
transform() fails due to an ambiguous function
grade() may throw exceptions which ain't what we want
so we need to write a wrapper, grade_aux

function signatures are actually legal in the middle of a prototype.  o.o
eg this:

    void write_analysis(
        std::ostream& out,
        const string& name,
        double analysis(const vector<StudentInfo>&),
        const vector<StudentInfo>& did,
        const vector<StudentInfo>& did_not
    );

This is 100% valid code o.O

accumulate() is doing a similar thing to sum().  it's sort of like a reduce() as
well, except that it's always doing the + operator.

there's also remove_copy() -- this copies a list while filtering out a certain value
it's something like (filter #(not (= % val)) foo).  

Note that remove_copy does not modify the array.

so you can remove all zeroes quite easy.

## 6.3 Classifying students, revisited

6-3-2: They give a library function that works slightly like 'partition' would.
And it's even called partition.  They use stable_partition though.


Algorithms act on the elements of containers but never the container itself.
Eg they don't change the size of containers.

Details:

* The static storage class modifier causes storage to persist across scopes
* "Iterator adapters" are functions that yield iterators, one is `back_inserter`
* Algorithm defines:
** accumulate, find, find_if, search, copy, remove_copy, remove_if, remove_copy_if
** remove, transform, partition, stable_partition
* `if` variants take a predicate instead of a concrete value

FINISHED ch6!
