*This project has been created as part of the 42 curriculum by marcde-c, dieandra.*

# push_swap

## Description

`push_swap` is a 42 project whose goal is to sort a list of integers using two
stacks and a restricted set of operations.

At the beginning, stack `a` contains the input values and stack `b` is empty.
The program does not print the sorted numbers. Instead, it calculates and prints
a sequence of Push_swap instructions that leaves stack `a` sorted in ascending
order and stack `b` empty.

The allowed operations are:

* `sa`, `sb`, `ss` — swap the first two elements of one or both stacks;
* `pa`, `pb` — move the top element from one stack to the other;
* `ra`, `rb`, `rr` — rotate one or both stacks;
* `rra`, `rrb`, `rrr` — reverse rotate one or both stacks.

This version implements four sorting strategies:

* `--simple` — an `O(n²)` minimum-extraction strategy;
* `--medium` — an `O(n * sqrt(n))` chunk-based strategy;
* `--complex` — an `O(n log n)` binary radix strategy;
* `--adaptive` — selects one of the previous strategies according to the
  measured disorder of the input.

The adaptive strategy is used by default when no selector is provided.

In this project, algorithmic complexity is measured by the number of Push_swap
operations generated, not only by the internal execution time of the C code.

## Instructions

Compile the project with:

```sh
make
```

Other available Makefile rules are:

```sh
make clean
make fclean
make re
```

Run the program by passing a list of integers:

```sh
./push_swap 4 67 3 87 23
```

The values may also be passed inside a single quoted argument:

```sh
./push_swap "4 67 3 87 23"
```

A sorting strategy can be selected explicitly:

```sh
./push_swap --simple 5 4 3 2 1
./push_swap --medium 5 4 3 2 1
./push_swap --complex 5 4 3 2 1
./push_swap --adaptive 5 4 3 2 1
```

`--adaptive` is the default behavior:

```sh
./push_swap 5 4 3 2 1
```

The selector flag may be provided together with the input values. Invalid or
unknown flags are treated as errors.

## Verifying the result

The output can be sent to the checker provided for the project:

```sh
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker_linux $ARG
```

A valid sequence produces:

```text
OK
```

The number of generated operations can be counted with:

```sh
ARG=$(shuf -i 0-9999 -n 100)
./push_swap $ARG | wc -l
```

For a 500-number test:

```sh
ARG=$(shuf -i 0-9999 -n 500)
./push_swap $ARG | wc -l
```

## Benchmark mode

The optional `--bench` flag prints information about the selected strategy and
the generated operations.

```sh
ARG="4 67 3 87 23"
./push_swap --bench $ARG
```

Benchmark information is written to the standard error, while the operation
sequence remains on the standard output. This allows both streams to be handled
separately:

```sh
ARG="4 67 3 87 23"
./push_swap --bench $ARG 2> bench.txt | ./checker_linux $ARG
cat bench.txt
```

The benchmark includes:

* the initial disorder percentage;
* the strategy selected;
* its theoretical complexity class;
* the total number of operations;
* the count of each individual operation.

## Input and error handling

The program accepts signed integer values within the `int` range.

It detects errors such as:

* non-numeric arguments;
* duplicated values;
* values below `INT_MIN` or above `INT_MAX`;
* empty arguments;
* malformed numbers;
* invalid strategy flags.

In case of an error, the program writes:

```text
Error
```

to the standard error.

Examples:

```sh
./push_swap 1 2 two 3
./push_swap 1 2 2 3
./push_swap 2147483648
./push_swap ""
./push_swap --unknown 3 2 1
```

When no values are provided, the program displays nothing.

## Project structure

```text
.
├── Makefile
├── README.md
├── includes/
│   └── push_swap.h
├── main.c
├── srcs/
│   ├── operations/
│   │   ├── op_log.c
│   │   ├── push.c
│   │   ├── reverse_rotate.c
│   │   ├── rotate.c
│   │   └── swap.c
│   ├── sort/
│   │   ├── sort_adaptative.c
│   │   ├── sort_chunk.c
│   │   ├── sort_init.c
│   │   ├── sort_print_bench.c
│   │   ├── sort_radix.c
│   │   ├── sort_small.c
│   │   └── sort_strategy.c
│   └── utils/
│       ├── libft_utils/
│       ├── parser_utils/
│       └── stack_utils/
└── tester.sh
```

The main responsibilities of these parts are:

* `main.c` initializes the stacks and strategy information, parses the input,
  calculates the initial disorder and starts the selected sorting strategy.
* `srcs/operations/` contains the eleven Push_swap operations and the centralized
  operation counter/output logic.
* `srcs/sort/` contains the four sorting strategies, adaptive selection and
  benchmark output.
* `srcs/utils/parser_utils/` validates and converts the program arguments.
* `srcs/utils/stack_utils/` creates, indexes, inspects and frees the stacks.
* `srcs/utils/libft_utils/` contains the utility functions required by the
  project.
* `tester.sh` provides additional tests for correctness, errors, stress cases
  and memory handling.

## Stack representation

The two stacks are represented as linked lists.

Each node stores:

* the original integer value;
* its sorting index;
* a pointer to the next node.

The sorting index represents the position that a value would occupy in the
fully sorted stack.

For example:

```text
Values:   42  -10  100   7
Indexes:   2    0    3   1
```

Using indexes allows the sorting algorithms to work independently of the
magnitude and sign of the original values.

The first node of each linked list represents the top of its stack.

## Disorder metric

The disorder metric is calculated before any Push_swap operation is executed.

It represents the fraction of pairs that appear in the wrong relative order:

```text
disorder = inverted_pairs / total_pairs
```

For every pair of positions `i < j`, the pair is considered inverted when:

```text
a[i] > a[j]
```

The number of possible pairs is:

```text
n * (n - 1) / 2
```

The resulting value is between `0` and `1`:

* `0` means that the input is already sorted;
* `1` means that the input is in completely descending order;
* intermediate values represent partially disordered inputs.

The metric is stored as a floating-point value so that the division does not
lose its fractional part.

## Algorithm and technical choices

### Simple strategy — `O(n²)`

The simple strategy adapts minimum extraction to the two-stack model.

While stack `a` contains more than three elements:

1. Find the position of its smallest value.
2. Rotate in the shortest direction until that value reaches the top.
3. Push it to stack `b` with `pb`.
4. Repeat the process.

The final three elements are sorted directly using a small set of cases. The
values stored in `b` are then returned to `a` with `pa`.

Finding and moving the next minimum may require a number of operations
proportional to the current stack size. Repeating this process for all elements
produces an `O(n²)` upper bound in the Push_swap operation model.

For inputs with five elements or fewer, this strategy is also used by the
adaptive mode to avoid the overhead of larger algorithms.

### Medium strategy — `O(n * sqrt(n))`

The medium strategy divides the sorted index range into moving chunks.

Its chunk size is proportional to the square root of the input size:

```text
chunk_size = floor(sqrt(n)) * 3 / 2
```

For very small inputs, a fixed chunk size of `4` is used.

During distribution:

1. An index window determines which values may be pushed from `a` to `b`.
2. Values inside the current window are pushed with `pb`.
3. Values in the lower half of the window are rotated inside `b`.
4. Values outside the window remain in `a` and are rotated with `ra`.
5. The window advances whenever an element is pushed.

This organization places lower indexes deeper in stack `b` and keeps higher
indexes closer to one of its ends.

During reinsertion, the greatest remaining index is located in `b`, moved to
the top through the shortest direction and returned to `a` with `pa`.

With a chunk size `k` proportional to `sqrt(n)`, distribution requires at most
`O(n² / k)` generated operations, while the chunk organization bounds the
reinsertion work by `O(n * k)`. Substituting `k = Θ(sqrt(n))` gives:

```text
O(n * sqrt(n))
```

The internal traversal used to locate a value does not itself generate
Push_swap instructions; the required complexity model counts the emitted stack
operations.

### Complex strategy — `O(n log n)`

The complex strategy is a binary LSD radix sort applied to sorting indexes.

For each bit, from the least significant to the most significant:

1. Inspect the current bit of every index in stack `a`.
2. Push indexes whose bit is `0` to stack `b` with `pb`.
3. Rotate indexes whose bit is `1` in stack `a` with `ra`.
4. Return all values from `b` to `a` with `pa`.
5. Continue with the next bit.

Because the indexes are in the range `[0, n - 1]`, they require approximately
`log₂(n)` bits.

Each bit processes every element a constant number of times, resulting in an
`O(n log n)` number of generated Push_swap operations.

Using indexes instead of the original values prevents the number of passes from
depending on the binary size of values such as `INT_MIN` or `INT_MAX`.

### Adaptive strategy

The adaptive strategy chooses an algorithm according to the initial disorder:

```text
n <= 5                  -> simple
disorder < 0.20         -> simple
0.20 <= disorder < 0.50 -> medium
disorder >= 0.50        -> complex
```

#### Low disorder

When disorder is below `0.20`, fewer than one fifth of all pairs are inverted.
The simple strategy is used because nearby minimum values often require short
rotations, avoiding the fixed overhead of chunk or radix processing.

Its worst-case upper bound remains `O(n²)`.

#### Medium disorder

Between `0.20` and `0.50`, the input still contains some useful local order, but
a quadratic strategy may generate too many operations.

The chunk strategy is used to distribute values through windows of size
proportional to `sqrt(n)`, resulting in an `O(n * sqrt(n))` operation bound.

#### High disorder

At or above `0.50`, the input is highly disordered and offers less useful local
structure.

The radix strategy provides a predictable `O(n log n)` operation bound
regardless of the original arrangement.

#### Small inputs

For five elements or fewer, the measured disorder may change significantly
because of only one inversion. The simple strategy is therefore selected
directly and handles these inputs with specialized small-stack logic.

## Complexity summary

| Strategy | Operation complexity | Auxiliary space |
|---|---:|---:|
| Simple | `O(n²)` | `O(1)` |
| Medium | `O(n * sqrt(n))` | `O(1)` |
| Complex | `O(n log n)` | `O(1)` |
| Adaptive | Depends on disorder | `O(1)` |

The linked-list stacks themselves require `O(n)` total storage. The auxiliary
space column refers to additional storage used by the sorting strategies.

## Performance targets

The subject defines the following operation-count targets:

| Input size | Minimum requirement | Good performance | Excellent performance |
|---:|---:|---:|---:|
| 100 numbers | fewer than 2000 | fewer than 1500 | fewer than 700 |
| 500 numbers | fewer than 12000 | fewer than 8000 | fewer than 5500 |

Results vary according to the input order and selected strategy. Tests should
therefore use multiple random sets rather than relying on a single execution.

## Suggested tests

The program should be tested with:

* no arguments;
* one value;
* two values in both possible orders;
* every permutation of three and five values;
* already sorted inputs;
* reverse-sorted inputs;
* negative and positive values;
* `INT_MIN` and `INT_MAX`;
* duplicated values;
* non-numeric values;
* empty strings;
* values outside the `int` range;
* each strategy selector;
* selectors in different argument positions;
* the `--bench` flag;
* random sets of 100 and 500 values;
* repeated stress tests.

The included tester can be executed with:

```sh
chmod +x tester.sh
./tester.sh
```

Memory errors and leaks can be checked with Valgrind:

```sh
ARG="4 67 3 87 23"
valgrind --leak-check=full --show-leak-kinds=all \
	./push_swap $ARG
```

Error paths should also be tested:

```sh
valgrind --leak-check=full --show-leak-kinds=all \
	./push_swap 1 2 two 3
```

## Contributions

Both learners participated in the review, testing and final validation of the
complete project and are able to explain and defend every part of the code.

### dieandra

* Implementation of `main.c` and the main program flow.
* Argument parsing and validation.
* Parser utility functions.
* Stack management and general utility functions.
* Input conversion, duplicate detection and integer-limit validation.

### marcde-c

* Implementation of all Push_swap operations.
* Centralized operation output and benchmark counting.
* Implementation of the simple sorting strategy.
* Implementation of the chunk-based medium strategy.
* Implementation of the binary radix strategy.
* Implementation of the adaptive strategy and strategy selection.
* Sorting-related benchmark output.

### Work completed together

* Definition and review of the adaptive disorder thresholds.
* Testing of valid inputs, error cases and memory handling.
* Review and debugging of the complete project.
* Validation of the generated operation sequences with the checker.
* Documentation and preparation for the defense.

## Resources

Useful resources for this project:

* The 42 `push_swap` subject.
* The 42 Norm and `norminette` documentation.
* C documentation about linked lists, integer limits and bitwise operations.
* Donald Knuth, *The Art of Computer Programming, Volume 3: Sorting and
  Searching*.
* Robert Sedgewick and Kevin Wayne, *Algorithms*, sections about radix sorting.
* Valgrind documentation for memory testing.
* Manual pages for:

  * `read`
  * `write`
  * `malloc`
  * `free`
  * `exit`

The manual pages can be opened with:

```sh
man 2 read
man 2 write
man 3 malloc
man 3 free
man 3 exit
```

## AI Usage

AI tools were used only as study and review support during the development of
this project.

They helped with:

* understanding concepts related to sorting algorithms and complexity;
* clarifying parts of the subject and expected program behavior;
* reviewing some technical explanations used in the documentation;
* suggesting test cases and edge cases;
* organizing tests used to validate the program.

The algorithms, source code, technical decisions, debugging and implementation
were completed by the group.

The final code was written, reviewed, understood and tested by `marcde-c` and
`dieandra`.
