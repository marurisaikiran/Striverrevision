# Low-Level Design & CS Fundamentals — Interview Companion

A book-style LaTeX companion for the LLD / core-subjects interview round,
in the same format as the DSA companions in the parent repo.

Self-contained (carries its own `preamble.tex`). Source PDF: `lld.pdf`.

## Contents

1. **OOP Foundations & SOLID** — the four pillars, class relationships &
   UML (association / aggregation / composition / dependency), and the
   five SOLID principles with before/after refactors.
2. **Design Patterns** — all 22 Gang-of-Four patterns (creational,
   structural, behavioural): intent, when-to-use trigger, structure,
   complete C++, and trade-offs.
3. **LLD Case Studies** — Parking Lot, Elevator, Vending Machine,
   Tic-Tac-Toe, Splitwise, Notification System, Logger, Rate Limiter,
   each with clarify → entities → patterns → C++ skeleton.
4. **CS Fundamentals Q&A** — answer-first interview questions on OOP,
   DBMS, Operating Systems, and Computer Networks.

## Building

```bash
tectonic lld_main.tex
```

(Any LaTeX engine with the packages in `preamble.tex` works. The Q&A
chapter's `\question` / `\answer` macros and the book-specific running
header are defined in `lld_main.tex`.)
