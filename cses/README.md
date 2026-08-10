# CSES Problem Set — Problem-Solving Companions

Book-style LaTeX write-ups of CSES Problem Set sections, in the same format
as the Striver A2Z companions in the parent repo: each problem gets a
problem statement, pattern recognition, the algorithm, a hand-traced dry
run, complete compilable C++ (with headers), and time/space complexity.

This folder is self-contained (it carries its own `preamble.tex`).

## Books

| Book | Source PDF | Coverage |
|------|-----------|----------|
| **Dynamic Programming** | `cses_dp.pdf` | All 19 CSES DP problems (Dice Combinations → Counting Numbers) |
| **String Algorithms** | `cses_strings.pdf` | All 21 CSES String Algorithms (KMP/Z, Manacher, suffix automaton, suffix arrays, Burrows–Wheeler) |
| **Sliding Window & Two Pointers** | `cses_sliding_window.pdf` | 11 Sliding Window problems + 6 two-pointer/subarray problems from Sorting & Searching |

## Building

Each book has a `<name>_main.tex` at the folder root that `\input`s
`chapters/<name>.tex`. Build with [tectonic](https://tectonic-typesetting.github.io/):

```bash
tectonic cses_dp_main.tex
tectonic cses_strings_main.tex
tectonic cses_sliding_window_main.tex
```

(Any LaTeX engine with the packages in `preamble.tex` works too.)

## Structure

```
cses/
  preamble.tex                 shared style (boxes, code listings, headers)
  cses_dp_main.tex             \input chapters/cses_dp.tex
  cses_strings_main.tex        \input chapters/cses_strings.tex
  cses_sliding_window_main.tex \input chapters/cses_sliding_window.tex + cses_two_pointers.tex
  chapters/
    cses_dp.tex,      cses_dp/NN_*.tex
    cses_strings.tex, cses_strings/NN_*.tex
    cses_sliding_window.tex, cses_sliding_window/NN_*.tex
    cses_two_pointers.tex,   cses_two_pointers/NN_*.tex
```
