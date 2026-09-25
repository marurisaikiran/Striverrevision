# ICPC Training — Greedy, Bitwise, Number Theory

A LaTeX problem-solving book plus tested C++17 solutions for the first three
topics of the *ICPC Training* tracker (ICPC India online preliminary prep).

**Book:** [`ICPC_Training_Greedy_Bitwise_NumberTheory.pdf`](ICPC_Training_Greedy_Bitwise_NumberTheory.pdf) — 63 problems, same format as the CSES books in [`../cses`](../cses).

Each problem has: statement, source and level, pattern recognition, approach with
a correctness argument (exchange / lower-bound proofs for greedy), pseudocode,
a dry run, the C++17 solution, time/space complexity, and common pitfalls.

## Coverage

| Chapter | Tracker (CSES / CF / AtCoder) | Past ICPC India prelims | Total |
|---------|-------------------------------|-------------------------|-------|
| Greedy | 20 | 9 | 29 |
| Bitwise / XOR | 11 | 3 | 14 |
| Number Theory | 14 | 6 | 20 |

Prelim statements come from the contest PDFs in
[m-e-r-l-i-n/icpc-india](https://github.com/m-e-r-l-i-n/icpc-india) or from
CodeChef's archive. **Three 2020-21 Amritapuri problems** (Express the Number,
Break Merge and Sort, Minimum Weight Bi-Partition) survive only as solution
slides; their statements are reconstructed and clearly marked in the book.

## Layout

```
icpc-training/
  icpc_training_main.tex        book entry point (\input preamble + chapters)
  preamble.tex                  CSES-book style + pitfall / reconstruction boxes
  chapters/                     greedy.tex, bitwise.tex, number_theory.tex, ...
    greedy/NN_*.tex             one file per problem (same for bitwise/, number_theory/)
  greedy/NN_*.cpp               solutions (listings in the book are these files)
  bitwise/NN_*.cpp
  number-theory/NN_*.cpp
  tests/
    run_tests.py                compile everything, run all official samples
    <topic>/NN_*.k.in/.out      sample tests
    checkers/                   checkers for problems with several valid outputs
    stress/*_stress.py          random tests against exhaustive brute force
    stress/perf.py              timing on maximum-constraint inputs
```

## Testing

```bash
python3 tests/run_tests.py                 # 76 official samples, all pass
python3 tests/stress/greedy_stress.py      # brute-force comparisons
python3 tests/stress/bitwise_stress.py
python3 tests/stress/number_theory_stress.py
python3 tests/stress/perf.py               # worst-case inputs, all < ~1s
```

Samples and stress tests passing is strong evidence, not a judge verdict —
submit to the original judges to be certain.

## Building the PDF

```bash
tectonic icpc_training_main.tex
mv icpc_training_main.pdf ICPC_Training_Greedy_Bitwise_NumberTheory.pdf
```
