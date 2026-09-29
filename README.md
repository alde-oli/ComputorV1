<!-- YoRHa archive -->
```
▸ YoRHa // ARCHIVE — COMPUTORV1
```

A C++ command-line solver that parses a polynomial equation from a string, reduces it, and solves it up to degree 3, including complex roots.

| UNIT DATA | |
|---|---|
| Type | 42 Lausanne project · solo |
| Stack | C++ · Make |
| Status | ■ COMPLETE |

## ▸ Overview
The input goes through a staged parser (composition and syntax checks, `x` to `X` normalization, equation split, operator reduction, term splitting, power and coefficient merging) that produces one coefficient map per side. The equation is reduced to `P(X) = 0`, its degree is reported, and dedicated solvers handle degrees 0 to 3. Complex results use a custom `Complex` class. Higher degrees are only reduced. The parsing steps are documented on a sample input in `parsing.txt`. It prints the reduced form, the degree, the discriminant and the real or complex solutions; `-v` adds a step-by-step trace.

## ▸ Usage
```bash
make
./computor "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
./computor -v "X^3 - 6X^2 + 11X = 6"
./computor HELP
```
On a case-sensitive filesystem (Linux), `make` fails: the sources include `Complex.hpp` but the file is `inc/complex.hpp`. Renaming or copying the header to `inc/Complex.hpp` fixes the build.

---
<sub>▸ Archived by UNIT ALDE-OLI · [profile](https://github.com/alde-oli)</sub>
