# Striver Revision

A from-scratch, LaTeX-typeset problem-solving companion covering every problem in
**Striver's A2Z DSA Sheet** (and, for the Graphs section, merged with the additional
problems from **Striver's SDE Sheet**) — both from [takeuforward.org](https://takeuforward.org).

Each problem gets the same full treatment:

- **Problem statement**
- **Pattern recognition** — the keywords/shape that identify which technique applies
- **Algorithm derivation** with an informal correctness argument
- **Pseudocode / step-by-step algorithm**
- **Hand-traced dry run** on a concrete example
- **Complete, compilable C++ solution** (with all headers)
- **Time and space complexity analysis**

For Dynamic Programming problems specifically, solutions are carried through all four
stages where applicable — brute-force recursion, memoization (top-down), tabulation
(bottom-up), and space optimization — with a complexity comparison across stages.

Every chapter is built against a shared [`preamble.tex`](preamble.tex), and every
chapter is independently compilable as its own standalone PDF in addition to being
includable in a combined book.

## Chapters

| # | Chapter | Problems | PDF | Source |
|---|---------|----------|-----|--------|
| 1 | Greedy | 15 | part of [`main.pdf`](main.pdf) | A2Z |
| 2 | Binary Search | 32 | [`binary_search.pdf`](binary_search.pdf) (also in `main.pdf`) | A2Z |
| 3 | Heap | 15 | [`heap.pdf`](heap.pdf) | A2Z |
| 4 | Stack and Queue | 29 | [`stack_queue.pdf`](stack_queue.pdf) | A2Z |
| 5 | Binary Search Tree | 14 | [`bst.pdf`](bst.pdf) | A2Z |
| 6 | Trie | 6 | [`trie.pdf`](trie.pdf) | A2Z |
| 7 | Recursion | 22 | [`recursion.pdf`](recursion.pdf) | A2Z |
| 8 | DP on 1D Arrays | 6 | [`dp_1d.pdf`](dp_1d.pdf) | A2Z |
| 9 | DP on Grids | 6 | [`dp_grids.pdf`](dp_grids.pdf) | A2Z |
| 10 | DP on Subsequences | 10 | [`dp_subsequences.pdf`](dp_subsequences.pdf) | A2Z |
| 11 | DP on Strings | 10 | [`dp_strings.pdf`](dp_strings.pdf) | A2Z |
| 12 | DP on Stocks | 6 | [`dp_stocks.pdf`](dp_stocks.pdf) | A2Z |
| 13 | DP on LIS | 7 | [`dp_lis.pdf`](dp_lis.pdf) | A2Z |
| 14 | MCM and Partition DP | 6 | [`dp_partition.pdf`](dp_partition.pdf) | A2Z |
| 15 | DP on Squares in a Matrix | 2 | [`dp_squares.pdf`](dp_squares.pdf) | A2Z |
| 16 | Graphs: Basics and Traversals | 8 | [`graph_basics.pdf`](graph_basics.pdf) | A2Z + SDE |
| 17 | Graphs: BFS and DFS Problems | 6 | [`graph_bfs_dfs.pdf`](graph_bfs_dfs.pdf) | A2Z + SDE |
| 18 | Graphs: Topological Sort | 7 | [`graph_topo_sort.pdf`](graph_topo_sort.pdf) | A2Z + SDE |
| 19 | Graphs: Shortest Path Algorithms | 8 | [`graph_shortest_path.pdf`](graph_shortest_path.pdf) | A2Z + SDE |
| 20 | Graphs: MST and Disjoint Set | 8 | [`graph_mst_dsu.pdf`](graph_mst_dsu.pdf) | A2Z + SDE |
| 21 | Graphs: SCC, Bridges, Articulation Points | 3 | [`graph_others.pdf`](graph_others.pdf) | A2Z + SDE |

**226 problems** across **21 chapters** (Greedy and Binary Search are also bundled
together into one combined book, [`main.pdf`](main.pdf)).

The Graphs chapters merge the A2Z Sheet's Graph step (38 problems across six lecture
groups) with the SDE Sheet's Graph section (18 problems); the only problem unique to
the SDE Sheet that A2Z didn't already cover is **Clone a Graph**, folded into the
Graph Basics chapter.

## Repository structure

```
.
├── preamble.tex              # shared LaTeX preamble (packages, custom boxes, commands)
├── main.tex / main.pdf       # combined Greedy + Binary Search book
├── <chapter>_main.tex        # standalone main file for each chapter, e.g. heap_main.tex
├── <chapter>.pdf             # compiled standalone PDF for each chapter
└── chapters/
    ├── <chapter>.tex         # chapter file (intro + \input of every section below)
    └── <chapter>/
        └── NN_problem_name.tex   # one file per problem/section
```

Every chapter follows the same pattern: `<chapter>_main.tex` does
`\input{preamble.tex}` then `\input{chapters/<chapter>.tex}`, which in turn
`\input`s each numbered problem file under `chapters/<chapter>/`.

## Building from source

PDFs are compiled with [Tectonic](https://tectonic-typesetting.github.io/), a
self-contained, dependency-fetching LaTeX engine:

```bash
tectonic <chapter>_main.tex
```

This produces `<chapter>_main.pdf`, which is then renamed to `<chapter>.pdf` in this
repo. No local TeX Live installation or package management is required — Tectonic
fetches what it needs automatically on first run.

## Custom LaTeX environments

Defined once in `preamble.tex` and reused throughout every chapter:

- `patternbox` — pattern/keyword recognition for identifying the technique
- `ideabox` — key idea, recurrence, or greedy choice
- `complexitybox` — time/space complexity (supports per-approach titles, e.g.
  `[Approach 2 Complexity]`)
- `takeawaybox` — concluding lesson tying the problem back to a broader principle
- `\problemstatement{...}` and `\dryrun{...}` — formatted problem statement and
  dry-run intro commands

## Source material

Problem lists are sourced from:

- [Strivers A2Z DSA Course/Sheet](https://takeuforward.org/dsa/strivers-a2z-dsa-sheet-learn-dsa-a-to-z)
- [Strivers SDE Sheet](https://takeuforward.org/interviews/strivers-sde-sheet-top-coding-interview-problems) (Graphs section only, merged into the A2Z Graph chapters)

All explanations, derivations, and code in this repository are original written
content for personal revision — credit for curating the problem lists themselves
goes to Striver (Raj Vikramaditya) and the takeuforward.org team.
