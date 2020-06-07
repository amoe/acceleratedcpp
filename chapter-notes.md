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

## Chapter 7

"Associative containers" -- aka hash tables or maps have keys.  An index of a
vector could be considered a type of key, with the following caveat: "Every time
we insert or delete an element form a vector, we implicitly change the index of
every element _after_ the one we touched".

From the word-counting example, we know that the map<foo, int> implicitly
initializes its ints to zero.  (Lazily at lookup time.)  This is called 'value
initialization'.

The `it->first`, `it->second` pattern is implemented by a type called
`std::pair`.

    for (iter it = counters.begin(); it != counters.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }

Here, `it` is of type `pair<const string, int>`.  The pair itself is an lvalue
but the const type of 'first' prevents modifications.

K&M say that you need to write `map<string, vector<int> >` (note the weird
space) to unconfuse the compiler, though I don't think this is the case.  (This
fails in C++98 but was defined in C++03)

I wrote this implementation based on a Clojure one which does a tree-recursion
using a recurse-inside-map pattern.  This is a bit easier because you don't
need to flatten the list afterward.  They use an accumulator pattern which is
tail recursive.  nrand is left undefined.

cstdlib header defines rand.  Why is nrand necessary?  There's some quirkiness
to rand-in-range with C++, as a result there are about 4 different approaches to
this simple problem.

They avoid using the [] lookup (the bracket operator) because it auto creates
the key, apparently ?!  at() is c++11

Look at this (regarding the bracket operator):

> If k does not match the key of any element in the container, the function
> inserts a new element with that key and returns a reference to its mapped
> value. Notice that this always increases the container size by one, even if no
> mapped value is assigned to the element (the element is constructed using its
> default constructor).
> A similar member function, map::at, has the same behavior when an element with
> the key exists, but throws an exception when it does not.

Bonkers.
Maps are not typically implemented using hash tables.  Rather they are backed by
'balanced self-adjusting trees'.

## Chapter 8

There are five types of iterator.  What does this mean?

We write a generic median function.  It works on any type vector<T>.
But how do we know that we can add types of T together?  There's no typeclass
system.

This syntax `template <class T>` is called the TEMPLATE HEADER.  T is called a
TYPE PARAMETER.

Note this line:

    typedef typename vector<T>::size_type vec_sz;

WTF does this do?  `typename` is special syntax that's required to be used
in the case where type parameters are present in a type name.

"We can't call median for a vector<string> because the median function uses
division and the string type does not have a division operator."

If we do try, we get this error:

```
build/ch8_generic.cc: In instantiation of 'T median(std::vector<T>) [with T = std::__cxx11::basic_string<char>]':
build/ch8_generic.cc:47:37:   required from here
build/ch8_generic.cc:30:38: error: no match for 'operator/' (operand types are 'std::__cxx11::basic_string<char>' and 'int')
         return (v[mid] + v[mid - 1]) / 2;
                ~~~~~~~~~~~~~~~~~~~~~~^~~
```

So basically the compiler tries to 'instantiate' the template, and complains
that it can't match `"fry" / 2` for example.

Instantiation seems to be taken very literally, eg multiple function objects
being generated in the resulting code.

Instantiation often happens at link time.


In this call:

    accumulate(v.begin(), v.end(), 0.0)

The 0.0 is of type double.  That ensures that the accumulator containing the sum
receives the type double also.  Otherwise we'd get an all-integer summation.

If we'd used 0, note that 0 + 1.2 would still be defined, so no error would
happen.  but presumably the summation would lose precision at every step, and
would ultimately be returned as an int.

They make an argument for having to pass the start and end points of collections
explicitly.  Certainly, I find the argument for rbegin() and rend() convincing.
[And bear in mind things like back_inserter.)
The idea of abstracting this iteration protocol is quite convincing.  Apparently
it's totally possible to overload the libraries to accept collections directly
but "it's far from clear that the extra convenience would outweigh the extra
complexity in the library" (LOL).

Not all algorithms work with all iteration variants.  sort() has the most
requirements and only works with vector and string iterators.  So don't try to
sort a list.  K&M go on to describe each type of iterator.

### Iterator types

Sequential read-only access -- You can only do ++ and *.

Why is the template header syntax using the `class` keyword?

It's not that clear why the caller's variable doesn't get modified.  I think
that this happens because the copy constructor is called on the iterator.

There's a tower of iterators.  An *INPUT ITERATOR* is this simplest form of
iterator.  The supported operations are:

   ++x
   x++
   *x
   x == something
   x != something
   x->some_field

An *OUTPUT ITERATOR* is the next step.  This is exemplified by std::copy from
the <algorithm> header.

There is an additional requirement, and that's a write-once requirement.  If
something is an output iterator, you're only allowed to execute *x = "foo"
ONCE.  Then you must execute ++x.  However this is a requirement only on this
low-level of the iterator tower.  Therefore only back_inserter is affected by
this.  Something like v.begin() is a more complete iterator, and therefore does
not suffer from this restriction.  However at template write time you won't be
able to tell whether your iterator has this feature AFAICT.  And I don't know
if the compiler can pick it up.


The next one is a *FORWARD ITERATOR*.  This means that you want read-write
access.  But you only need it sequentially.  The example is std::replace, which
replaces `old_value` with `new_value`.  So it's obvious that here you need:
*x = foo, *x, and ++.  This also removes the write-once requirement of plain
output iterators.  We don't have --x still, though.

The next version ALSO supports `--`, and that's called a *BIDIRECTIONAL
ITERATOR*.

The next level is a *RANDOM-ACCESS ITERATOR*.  It requires the ability to
subtract iterators and add integers to iterators.  It also requires x[n], the
indexing syntax, and p > q -- the ability to compare iterators and see which are
larger or smaller.

Vectors and strings are random-access iterators but lists are not.

You use != and == in iterator loops because this imposes the smallest set of
requirements on the iterator.  Even an input iterator, the lowest tower level,
supports == whereas it may not support the `<` operator.  So by writing loops
with == end as a stopping condition, we make the fewest assumptions.

Some functions can use x.end() as an error code when they return.  This is a
funky solution to the lack of an Optional / Maybe type.

Using stream iterators in <iterator>, you can wrap I/O streams in iterators.
Using this call 

    copy(my_stream_iterator, sentinel, back_inserter(v));

You can treat the stream as if it was just a container type.  Sentinel is a
magic value that seems equal to any stream iterator with an EOF condition.

Very inconveniently, template functions must be declared within a header file.

In the case where you just return a value of type T the compiler doesn't know
how to instantiate the template:

    double x = zero();

The compiler doesn't know that a `double` is expected.  So it can't deduce the
type parameter T.  You have to write instead.

    double x = zero<double>();


## Chapter 9

Defining new types.

> It is worth reviewing why we are using the fully qualified names for
> std::string and std::vector [instead of `using`].  ... Code that is intended
> for use by others should contain the minimum number of declarations necessary.
> ... As a matter of good practice, we use the qualified names in code that goes
> into header files, [but not in source files].

The double-equals :: is being referred to as the 'scope operator' and is the
same operator (in some sense) as the one in `string::size_type`.

Remember that the `this` is a reference.  I can't see if that really has
implications.  For instance the type of `this` in a StudentInfo member function
is `StudentInfo&`.

Look at this:

    double StudentInfo::grade() const {
        return ::grade(midterm, final, homework);
    }

The empty scope operator forces a call to the non-member function `grade`.
Otherwise, this would be an attempted recursion on the member function.  

The member function is const qualified.  If you have a function that accepts a
StudentInfo with the signature `foo(const StudentInfo&)` you'll only be able to
call const members of StudentInfo.  This seems quite useful and I can't think
of an analogous thing in Java.

Compare function?  We compare two students based on their name.

"If a function changes the state of an object, then it ought to be a member of
that object."

There is some advantage to defining this as a global function rather than a
class function (not shown which, deferred at pg159.)

They refer to 'public', 'private' as a 'protection label'; the more standard
term is "access specifier".

A member function cannot have the same name as a member variable.

Defining a simple member function at the point of declaration can actually
serve as a hint to the compiler to inline that function.

> Accessors should be provided only when they are part of the abstract interface
> of the class. ... Notion of a student name is part of our abstraction, and it
> is fitting to provide a name() function.

So basically provide accessors on a JIT basis and question whether behaviour
could be moved into the class.  This will always be subjective.

An automatically generated constructor is called a "synthesized constructor"
in ACPP.

Primitives are 'default-initialized' meaning that they can contain garbage
(dangerous).
Containers are either empty or 'value-initialized' which means they get zero
values.

Initializer lists will execute before the body of constructors.  Hence, if you
assign in the constructor body explicitly you are overwriting the value
that was initialized before.  ALWAYS initialize built-in types.  Anything else
will be implicitly value-initialized.

Initializer lists are executed in the order of declaration.  So if multiple data
members depend on each other, just eschew the initializer lists, and use the
constructor body to assign them instead, which makes the order-dependency more
clear.


## Chapter 10

They will introduce arrays and pointers.

"An array is a kind of container; a pointer is a kind of random-access
iterator."

They introduce this backwards.

To take the address of an object x, write `&x`.  In this context, `&` is called
the **address operator**.  While `*p` is using the **dereference operator**.

> The constant 0 is the only integer value that can be converted to a pointer
> type

Interesting.  So, in C++ we use `char *foo = 0`;

Pointers have types, but why?  They don't need a type to contain their value.
eg a pointer to `int64_t` has the same size as a pointer to `int32_t`.
Obviously though they do need types when you dereference them, and also when you
do arithmetic on them.

K&M mention a weirdness of the type notation for pointers:

    int* p, q;

In this example, p is defined as a pointer, but q is NOT defined as a pointer!
Although it looks like it should be.
Just never declare multiple variables on the same line to avoid this problem.

The name of a bare function turns into a pointer to that function automatically.
Whenever we say `find_if(x.begin(), x.end(), is_negative)` we are passing a
function pointer.  It doesn't matter that it happens to be a template parameter
in this case, it still just becomes a function pointer.

`size_t` is the type denoting the size of an array.  The size of an array must
be known at compile time.

Whenever we use the name of an array as a value, that value is a pointer to the
initial element of the array.

eg:
    double coords[3];
    *coords = 1;   // initial element is 1


Here's how we can create a memory unsafe program:

    vector<double> dv;
    const int number_of_dimensions = 3;
    double coords[number_of_dimensions] = {4,5,6};
    copy(
        coords,   // Has a pointer type
        coords + 3,  // Is still usable for comparisons
        back_inserter(dv)
    );


    using iter_t = vector<double>::const_iterator;
    for (iter_t it = dv.begin(); it != dv.end(); it++) {
        cout << *it << endl;
    }

The final value of `dv` is an arbitrarily-valued point in memory.

    Starting.
    x = 5
    x = 6
    result (call-through-pointer) is 16
    4
    5
    6
    4.6457e-310
    End.

The final value changes with every run.

Pointers support the indexing operator.  Indexing provides the value itself
inside a given array.

Evaluating 'sizeof' on an array will give you the entire size of that array in
bytes.  I find this surprising because I thought that it gave the element
number, but it doesn't, I must have misremembered.  Also why doesn't sizeof
decay to a pointer?  

When attempting to call main we get 'ISO C++ forbids converting a string
constant to char*'.  Why?

discuss cerr and clog..  Cerr is unbuffered!  clog should be the default choice.

ifstream  and ofstream are used for writing to files.

For historical reasons interactions with fstream classes often take character
arrays rather than C++ strings.  If you want to use a std::string, you have to
coerce it to a C-style string using `c_str()` member function. -- C++11 added a
new constructor for ifstream that accepts plain strings.


