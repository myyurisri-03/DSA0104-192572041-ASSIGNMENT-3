# DSA01-<RegisterNumber>-Assignment3

**Course:** DSA01 | **CO3:** Constructors, Destructors and Operator Overloading (C++)

| | |
|---|---|
| Name | [Your name] |
| Register Number | [Your register number] |
| Compiler | g++ 13.3.0 (Ubuntu 24.04) |
| Compile command | `g++ -std=c++17 -Wall -Wextra <file>.cpp -o <name>` |
| Sanitizer command | `g++ -std=c++17 -Wall -Wextra -fsanitize=address -g <file>.cpp -o <name>` |

> Before submitting: replace the placeholders above, re-run `bash run_all.sh` on **your own machine**,
> compare with the outputs in this repository, and add your screenshots to each Q folder.
> Make at least one Git commit per task (e.g. `git commit -m "Q3: seat map completed"`).

## How to run

```bash
bash run_all.sh                       # builds and runs everything; writes compile_*.txt and output_*.txt in each Q folder
# or one program by hand:
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g Q2/prescription.cpp -o prescription && ./prescription
```

For the `-O0` / `-O2` timing in Q5 the script builds `bench_increment.cpp` twice.
Timings differ from machine to machine, so your numbers will not match the ones stored here.

## Folder contents and results

### Q1 – Constructors and overloading
| File | Purpose | Result |
|---|---|---|
| `book.cpp` | Default, parameterised and overloaded constructors, delegation, validation | All three objects print; `copies = -3` rejected with `invalid_argument` |
| `book_no_default.cpp` | Default constructor removed | Compile error: `no matching function for call to 'Book::Book()'` (see `compile_book_no_default.txt`) |
| `reorder_demo.cpp` | Wrong initialisation order | `-Wreorder` and `-Wuninitialized` warnings; `first` holds garbage (see `compile_reorder_demo.txt`) |
| `explicit_demo.cpp` | `explicit` constructor | Compiles normally; with `-DUSE_EXPLICIT` it fails (`compile_explicit_fail.txt`) |
| `book_default_args.cpp` | Alternative design: default arguments | Works, but `Book("Gitanjali")` gets `copies=0`, not 1: default arguments cannot give the donated-book case its own default |

### Q2 – Copy constructors
| File | Purpose | Result |
|---|---|---|
| `prescription.cpp` | Completed TODO 1–3 (deep copy, copy assignment, destructor) | `Ibuprofen ORS \| Paracetamol Cetirizine \| Paracetamol ORS`; clean under AddressSanitizer |
| `prescription_shallow.cpp` | Version without copy constructor | AddressSanitizer reports **heap-use-after-free** in `~Prescription()` (the second destructor touches the array the first one freed; the same root cause as a double delete) |
| `prescription_experiments.cpp` | Copy count, self-assignment, timing | By value: 1 copy; by `const&`: 0 copies; `p = p` leaves data unchanged; timing grows about linearly with n |
| `prescription_vector.cpp` | Alternative: `std::vector` (Rule of Zero) | Same expected output, no copy functions written |

### Q3 – Dynamic constructors and destructors
| File | Purpose | Result |
|---|---|---|
| `seatmap.cpp` | 2-D seat map with `new`/`delete[]`; stack, block, heap, zero-row events | Message order: `+Stack +Block -Block +Heap -Heap +Empty -Empty -Stack`; clean under ASan |
| `seatmap_leak.cpp` | `delete` forgotten on purpose | LeakSanitizer: `detected memory leaks` |
| `logger_predict.cpp` | Predict-the-output program | `+A +B -B copyAc use -Ac +P -P end -A ` |
| `seatmap_memory.cpp` | Bytes allocated per size | 10x20: 280, 100x200: 20,800, 1000x2000: 2,008,000 bytes (rows+1 allocations) |
| `seatmap_flat.cpp` | Alternative: one contiguous block | Works with a single allocation |

### Q4 – Arithmetic and stream operators
| File | Purpose | Result |
|---|---|---|
| `money.cpp` | Completed TODO 1–2, carry and negative tests | `Rs 200.00`, `true`, `Rs 1.25`, `-Rs 3.50` |
| `money_bill_and_double.cpp` | Bill calculation, 1,000,000 additions of Rs 0.10 | `Money` is exactly Rs 100000.00; `double` ends at 100000.000001 (drift) |

### Q5 – Increment, comparison, subscript
| File | Purpose | Result |
|---|---|---|
| `time_playlist.cpp` | Prefix/postfix `++`, `==`, `<`, checked `[]` (const and non-const), roll-over | `a=0:59:58 b=1:00:00 t=1:00:00`; out-of-range index reported for -1 and size |
| `counter_predict.cpp` | Predict-the-output program | `5 7 7` |
| `bench_increment.cpp` | 10,000,000 increments and checked vs unchecked access | At `-O0` postfix is clearly slower; at `-O2` the difference disappears (see `output_bench_O0.txt`, `output_bench_O2.txt`) |

### Q6 – Rules of operator overloading
| File | Purpose | Result |
|---|---|---|
| `text.cpp` | `Text` class: Rule of Three, `+`, `==`, `!=`, `<<` | Correct output; clean under ASan (`-DNO_BENCH` skips the timing loop so ASan runs quickly) |
| copy count | `output_text.txt` vs `output_text_no_elide.txt` | 0 copy-constructor calls with copy elision, 2 with `-fno-elide-constructors` |
| timing | `output_text_O2.txt` | 100,000 concatenations: `Text` is several times slower than `std::string` |

### Q7 – Complex-number class
| File | Purpose | Result |
|---|---|---|
| `complex.cpp` | `Complex` class, series and parallel RLC (R=10, L=0.1 H, C=500 µF, ω=100) | Series `10 - 10j`, \|Z\|=14.1421; parallel `8 + 4j`, \|Z\|=8.9443; division by zero reported with `domain_error` |
| `complex_std.cpp` | Alternative: `std::complex<double>` | Same values; `R / 0` silently gives `(inf,-nan)` |

## Notes
- `compile_*.txt` holds compiler warnings/errors for each program; `output_*.txt` holds the program output and exit code.
- Programs that are expected to fail (`book_no_default`, `explicit_fail`) have no output file, only a compile error.
