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





















































rewrite the grammar program using a list as the data structure in which to build
the sentence.

This is using std::list which is just an STL container so it should be the same
code, only changing the types.  But we also need to change our printing function
as we need separate functions with separate type signatures to print a list.

I guess that this exercise is only here to demonstrate the need for generics.
