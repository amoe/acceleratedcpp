## Exercises ch0

### Compile and run the `Hello, world` program

Done.

### What does the following statement do?

3 + 4

Adds 3 and 4 and yield 7 as the result.

### 0-3

This implementation aligns tabs with the 8-character tab stop.

### 0-4

Done

### 0-5

This is *not* a valid program, and why?  I suppose that the braces are
absolutely required for functions.  "The body bof a function must be encosed in
braces even if it is only a single statement.

### 0-6

This should be a valid program because it just has an evenly numbered of bare
blocks.  And indeed it is.

### 0-7

I don't believe that this is valid, because comments do not nest as such.

### 0-8

Although this one is indeed valid

### 0-9

the shortest valid program would surely just be `int main(){}`
Because `main` is specially allowed to omit return by the spec.

### 0-10

## Exercises ch1

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


## Exercises ch2

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

## Exercises ch3

### 3-0 -- Done.

### 3-1 -- No idea how to do this.  

Well yeah, imagine that we have read the values

1, 2, 4, 8

Now imagine that we discard the value 4

If we then read another value 16, the median should be 4.

But we discarded it, therefore it will incorrectly be seen as (2+8)/2 = 5.

### 3-2

This exercise is weird, I couldn't do it properly.

### 3-3 

Done with a weird solution

### 3-4

Done with no problems

### 3-5

I'm too lazy to do this one, it's mostly boring book keeping.

### 3-6

Find what does division by zero do.
It makes a floating point exception and crashes the program.  It also generates
a message in dmesg `trap divide error`!  It's shocking that this doesn't happen
literally all the time.  The adaptation is pretty simple, you just change it
to check if count == 0 after the loop and bail out if this is the case.

## Exercises ch4

### 4-1

  in this example, X has a type of std::string::size(), ie size_type of
a string.  But maxlen is an int.  Therefore it won't work.  You could fix it
by defining maxlen as `string::size_type`.

### 4-2

This is not so hard, we pad to 2 digits using cout.width(), and note that
the width gets reset after every call.

### 4-3

Now generalize to allow arbitrary maximums -- If we don't change it, then
the width gets wrong because at 1000 boundary, it should be padded to 3 instead.
This is interesting because you need to calculate the number of digits in the
number to know how it will be printed.  I used this function to do so:

    int nDigits(int n) {
        int result = 0;

        while (n >= 1) {
            n /= 10;
            result++;
        }

        return result;
    }

And indeed this is the approach that Johnny Chan uses.

### 4-4.

Not doing this.

### 4-5.

### 4-6

This is more interesting, but I'm still going to skp it.

### 4-7

Found out that << fixed << setprecision() is necessary to actually show zeros
at the end of a double.  The program is easy and completed.

### 4-8

We can infer that the return type of f is vector<double>, barring the fact that
it might also be an array which we don't know yet.

## Exercies ch5

### 5-0 -- Done.
### 5-1 -- Done as a Python program, see the python playground.
### 5-2
 Written the vector version, generated three test files using a perl
program..  Time is fine for 10 elements, then sortof OK for 1000 elements,
and with 10,000 it becomes insanely slow!  This is a really interesting exercise
on performance.
It takes 98 seconds!  for 10,000 records for an insanely simple operation
And that's jsut because erase() is slow on vectors

The list version, on the other hand, takes a tiny bit less...  Not sure why

### 5-3

This is implemented, it's fairly simple but at this stage we only have the
knowledge to be able to define a specific typedef like so:

typedef list<StudentInfo> student_sequence;

We aren't able to implement sort yet, because sort has to be handled differently
depending on the relevant container type.


### 5-5


center() returns a picture in which all the lines of the oroginal picture are padded out
to their full width and the padding is as evenly divided as possible between the
left and right sides of the picture.  What are the properties of pictures for which suh a
function is useful?  How can you tell whether a given picture has those properties?

This is an extension of the programs in 5.8.1.  You can find the existing
programs in ch5_iterators.

The properties of the pictues for which the function is useful is any function
which has some strings with different lengths from the others, I'd say.

You can tell whether a picture has the property by implementing an algorithm
to test if all string size() are the same, eg:

   string last_line;
   boolean all_same = true;
   for (string in picture) {
       if (last_line.size() != string.size()) {
           all_same = false; break;
       }
   }

Just a linear search essentially

Honestly getting pretty bored of this chapter and its insane number of exercises,
I cba to do them all, even though it's probably a nice exercise.  They're all
just variations on linear search.


### 5-10

Palindromes: Use the reverse iterator of a string to spell it out backwards.
Now just compare the original and the reversed one.  If reversed == original,
it's a palindrome.

To extend to find the longest, just check it's palindome, then get the string
size().  Overwrite `max_so_far` if it's larger than `max_so_far`.


### 5-11 -- Ascenders & descenders

Write a program to determine if one word has extenders and descenders.
Pretty easy, you just declare the letters as such:

vector<string> ascenders = {"b", "d", "f", "h", "k", "l", "t"};

Iterate through the string using  the string's iterator.
Then linear-search a match in ascenders and descenders.

To extend, just do the same but hold the max.

## Exercises ch6

### 6-0 -- Done.
### 6-1 -- Done in ex6_1.cc.

The main thing to note is that we iterate over words.  We can use a const
iterator.  words[i].size() becomes it->size().
In hcat, we have two iterators that we move in parallel.

### 6-2 -- Done in ex6_2.cc

### 6-3

> What does this program fragment do?

    vector<int> u(10, 100);
    vector<int> v;
    copy(u.begin(), u.end(), v.begin());

I thought that this would copy u into v.
However, this actually gives a segfault for me.
I presume because v hasn't been allocated properly, to have 10 spaces.
Indeed, pre-allocating v causes it to work.

### 6-4

Correct the program, there are two ways.  One way is to pre-allocate the vector
to correct size, the other is to use l.insert() instead of copy.  Prellocation
solution is probably better in this case.  But less flexible overall.

### 6-5

Already done in ch6_algorithms.cc.

### 6-6

Already done in ch6_algorithms.cc: `demo_comparing_grading_schemes`.

### 6-7

> The portion of the grading analysis program from S6.2.1/110 that read and
> classified student records depending on whether they did (or did not) do all the
> homework is similar to the problem we solved in extract_fails. Write a function
> to handle this subproblem.

In short, the approach here is to reuse the `extract_fails_5` approach (which uses
`stable_partition`) and rework it using predicate function
`student_did_all_homework_p`.
We write `extract_incomplete_hw_students` and it seems quite simple.

### 6-8

> Write a single function that can be used to classify students based on criteria
> of your choice. Test this function by using it in place of the extract_fails
> program, and use it in the program to analyse student grades.

OK, so Mathalope uses a function pointer for this.  This is clearly gesturing
towards generic programming.  However I'm not sure that function pointers have
yet been introduced.  This is essentially a refactoring and it's done in
ex6_8.cc.


The signature looks like

    vector<StudentInfo> extract_with_criteria(
        vector<StudentInfo> students, bool criteria(const StudentInfo&)
    ) {
        ...
    }


### 6-9

Done in ex6_9.cc.
Note that this literal translation of fold-left won't work:

    return accumulate(v.begin(), v.end(), "");

because this tries to pass a `const char*` (the type of a literal string)
instead of an empty string.

This will work though:

    return accumulate(v.begin(), v.end(), string());

The key here is to realize that elements are combined using the `+` operator
which is defined on strings as well as on numbers.

FINISHED Ch6!


## Exercises ch7

### 7-1

Group word count by occurrences.  The invert-map solution is the same
one as suggested by Mathalope.

## 7-2

Ranges

A 90-100
B 80 - <90
C 70 - <80
D 60 - <70
F <60

output should list how many fall into each category

## 7-3

Deduplicate line number occurrences.  Just use a map with bool keys to emulate a
set.

## 7-4

Break long lines.  Think about the definition of this.  A small word looks like
this:

    Alice: [2, 5]

T is the token length.  = 5.
": " length = 2.
C++11 adds to_string for estimating the string length of integers.

## 7-5

rewrite the grammar program using a list as the data structure in which to build
the sentence.

This is using std::list which is just an STL container so it should be the same
code, only changing the types.  But we also need to change our printing function
as we need separate functions with separate type signatures to print a list.

I guess that this exercise is only here to demonstrate the need for generics.

## 7-6

> Reimplement the gen_sentence program using two vectors: One will hold the
> fully unwound, generated sentence, and the other will hold the rules and will
> be used as a stack.  Do not use any recursive calls.

So this is actually quite devious.  You can use the vector as a stack.

You can use pop_back() to remove the last element which is an efficient
operation.

HOWEVER -- your sentence is going to be in the wrong order -- why?
Because words will get put on to the stack and the last word will be processed
first.

I find it easier to use rbegin() and rend() to reverse the rule when it's being
added to the stack.  This makes the semantics like a queue.  And actually Johnny
Mathalope did the same solution.

## 7-7

Not so difficult, just an if condition.

## 7-8

Cross reference program except that it finds URLs and reports lines on which
distinct urls occur.  This is actually quite straightforward after factoring
out the url finding code from chapter 6 into a separate header file.

## 7-9

nrand() will not work for arguments greater than RAND_MAX

on some architectures RAND_MAX is 32767 while the maximum int is (2^31)-1

reimplement so it works well for all values of n.  But on my architecture,
RAND_MAX == INT_MAX...

We basically just keep picking numbers until one falls into the bucket.

However, if n >= RAND_MAX, that can't happen.  K&M have a solution that I don't
understand.

The key insight is really that if your system doesn't produce 'enough' to fill
the space, you just keep calling rand() until it does.  OTOH it's not that clear
how to fairly deal with remainders.  Eg if rand(65536) is requested, a fair
result can be obtained by calling rand() twice, adding the result and dividing
by 2, but in the case of odd numbers I'm not sure what would happen, and not
even sure how to measure the result.

# Chapter 8

## 8-1

Re p110:
Note that the analysis functions share the same behaviour, they only differ in
terms of the functions they call to calculate the final grade.  Write a template
function, parameterized by the type of the grading function, and use that
function to evaluate the grading schemes.

They refer to median_analysis, average_analysis, optimistic_median_analysis.

The confusing thing about this: There's actually zero need to template this,
because you can just use function pointers as parameters.  And the template
version is IMHO strictly inferior.

Function pointer version:

    using xform_t = double (*)(const StudentInfo&);

    double analysis(const vector<StudentInfo>& students, xform_t grading_function) {
        vector<double> grades;

        transform(
            students.begin(), students.end(),
            std::back_inserter(grades),
            grading_function
        );

        return median(grades);
    }

    void write_analysis(
        ostream& out,
        const string& name,
        xform_t grading_function,
        const vector<StudentInfo>& did,
        const vector<StudentInfo>& did_not
    ) {
        out << name
            << ": median(did) = " << analysis(did, grading_function)
            << ": median(did_not) = " << analysis(did_not, grading_function)
            << std::endl;
    }



## 8-2

Implement these functions:

* equal(b, e, b2)
* find(b, e, t)
* copy(b, e, d)
* remove_copy_if(b, e, d, p)
* transform(b, e, d, f)
* accumulate(b, e, t)
* search(b, e, b2, e2)
* find_if(b, e, p)
* remove_copy(b, e, d, t)
* remove(b, e, t)
* partition(b, e, p)

Try to use the lowest-common-denominator of iterator operations.

cplusplus.com has some good examples of using each function, but skip past the
definition.












search(b, e, b2, e2)
find_if(b, e, p)





partition -- wanted output is

True elements:
foo
False elements:
bar
baz

## 8-3

median takes arguments by values.  modify to pass iterator.
However it can't be a const iterator because we need to modify the vector.

What would you expect the performance impact to be?  We just avoid an O(n) copy.

10:42         amoe > In the book "Accelerated C++" they ask you to write a 'median()' function that operates on iterators rather than taking a vector.  They ask "if we did so, what would you expect 
                     the performance impact to be?"  What would the answer to this question be?  My answer would be that the iterator version avoids an O(n) copy of the vector, do you think that's 
                     correct?
10:45    causative > no, you wouldn't copy the vector, you'd pass it by reference or pointer
10:46         amoe > causative: They explicitly contrast it to a version with signature "double median(vector<double> v)"
10:47        ville > causative: but then it wouldn't be a function taking a vector
10:48        ville > amoe: and yes you would be correct
10:48         amoe > ok, I was just wondering if there was anything more to say in answer to that question
10:49    causative > well, what operations are you allowed to do on these iterators?  at some point you're going to need to partially sort the array to find the median efficiently
10:50    causative > so you'd end up having to either modify or copy the vector
10:50    causative > median-of-medians?
10:52    causative > I believe the runtime of median-of-medians would be substantially more than the time needed to make a copy
10:53    causative > er, hang on, median of medians is only an approximate median anyway.  I believe to find the actual median you need to actually sort
10:53    causative > (partially)
10:56    causative > e.g. you could do a quicksort-like algorithm where you only continue the sort on the side of the pivot where the median might reside
10:56         tane > causative, it's called "quickselect" :)
11:01    causative > if you don't copy the array you'd end up using the iterators for random access instead of iteration
11:02    causative > which doesn't seem idiomatic
11:02    causative > so I think you shouldn't do it that way
11:14      rindolf > causative: there is an O(N) median algorithm on an unsorted array
11:15    causative > yeah it's quickselect

## 8-4

Implement the swap function, why did we call swap rather than exchanging the
values of *beg and *end directly?  Try it and see

## 8-5

> Reimplement the `gen_sentence` and `xref` functions from Chapter 7 to use output
> iterators rather than putting their entire output in one data structure.  Test
> these new versions by writing programs that attach the output iterator directly
> to the standard output, and by storing the results in a list<string> and a
> map<string, vector<int>> respectively.

i.e. `xref` should be tested by attaching directly to the standard output.
How is this done?
See 8.4  where we templateize split.
Instead of returning a value we takean templated output parameter.
So wherever you push you now just increment the iterator.
An `ostream_iterator<TYPE>(cout, " ")` can be used to write to stdout.

Note that in the end we used the recursive version of gen_sentence from chapter
7 rather than the iterative version.  I don't know if the iterative version
is possible.






















xref seems impossible
yes it's impossible using a map iterator -- specifically

      ret[*it].push_back(line_number);

this associative lookup can't be done with an iterator

So we have to do something else ... and what they do is -- cheekily copy the
results to the output iterator!!! >.< >.<


> Suppose that m has type `map<int, string>` and that we encounter a call to
> `copy(m.begin(), m.end(), back_inserter(x))`.  What can we say about the type
> of x?  What if the call were `copy(x.begin(), x.end(), back_inserter(m))`
> instead?

The first thing is that back_inserter call must be valid.  That means that x
must have some type that supports `push_back`.  We also know that m.begin()
will yield `pair<int, string>`.  So we can infer that one valid type for x
would be `vector<pair<int, string>>`.

What if the call were `copy(x.begin(), x.end(), back_inserter(m))`?
This call fails!  Because m does not support `push_back`.
But it fails at copy time, after template expansion.  back_inserter() still
works.



## 8-7

> Why doesn't the max function use two template parameters, one for each argument
> type?

Well, let's try it.
It seems to work.
I don't know how it worked.
The fundamental problem is that the runtime return type could vary in that case,
which would cause 

    template <typename T, typename U>
    T my_max2(T a, U b) {
        if (a >= b) {
            return a;
        } else {
            return b;
        }
    }

to expand to

    double my_max2(double a, int b) {
        if (a >= b) {
            return a;
        } else {
            return b;   // ATTEMPT TO RETURN INT FROM DOUBLE FUNCTION
        }
    }

BUT this is a sneaky case I think where the compiler is cheating.
The compiler does implicit conversion from int to double that allows this 
specific case to pass.
What stuff can be compared?  Iterator maybe -- yes, iterators support comparison
operations and also expose the failure of this logic.

## 8-8

> Why didn't we write `(begin + end) / 2` instead of `begin + ((end - begin) / 2)

First confirm that these are actually identical which they are.
seems to me the answer is likely that (begin + end) yields an iterator which
does not support the division operator.

WRONG.  Actually (begin + end) is itself invalid, you can only add things that
are convertible to 'ptrdiff_t' (long) to an iterator.

But, you can subtract begin from end, why?
The actual answer is because the set of operations for random access iterators
mandates that p - q be supported, but not p + q.
Why?
The reason for this is that `p - q` returns an INTEGER, the DISTANCE between
two iterators, and does not itself return an iterator.  So it's in no way
equivalent to saying `p - 2` which returns an iterator.  As such, `p + q` would
not make any sense.

# Exercises ch9

## 9-1

Reimplement the studentinfo classs so that it calculates the  final grade when
reading the students' record and stores that grade in the object.  Reimplement
the grade function to use the precomputed value

## 9-2

> If we define the `name` function as a plain nonconst member function what
> other functions in our system must change and why?

The compiler tells us:

    bool compare(const StudentInfo& x, const StudentInfo& y) {
        return x.name() < y.name();
    }

StudentInfo is const so you can't call the now-non-const .name() member function
on it.  Fix is to remove const qualifiers from these parameters.

Nothing else uses const so it doesn't matter.
















































# 9-5

> Write a class and associated functions to generate grades for students who take
> the course for pass/fail credit.  Assume that only the midterm and final grades
> matter,  and that a stuent passes with an average exam grade score greater
> than 60.  The report should list the students in alphabetical order,  and
> indicate P or F as the grade.

# 9-6

>Rewrite pass/fail grading program so that it shows all students who passed
>then all students who failed.

The logical approach is stable_partition.  how to refer to member function
though

several interesting things here, need to create a free function to
print stuff.  use of stable_partition.

## 9-7

The read_hw function solves a general problem.  How would you integrate it with
StudentInfo?  (paraphrase)

The answer is just to make it private.


# 10

## 10-1

> Rewrite the student grading program from p166 to generate letter grades.
> (ch9)

This means the full completed chapter 9 program.  At the moment it generates
double grades.

## 10-2

> Rewrite the median function so that it works with either vectors or arrays.
> The function should allow containers of any arithmetic type.

Thought provoking problem.  We get around the main frustration by just saying
that the templat always returns `double`.   

This was actually 'wrong', we need to use the template calling code (not sure
where it's referred to) to templatize the return type as a separate type
variable.

https://github.com/bitsai/book-exercises/blob/master/Accelerated%20C%2B%2B/chapter10/10-2.hpp

## 10-3

> Write a test program to verify that the median function operates correctly.
> Ensure that calling median does not change the order of the elements in the
> container.


Eureka, now we can declare a vector of the result type, copy into it, and we
just use vec_sz to avoid the hassle of dealing with ptrdiffs.

## 10-4

> Write a class that implements a list that holds `string`s.

Hmm
