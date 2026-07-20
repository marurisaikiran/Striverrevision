# D. E. Shaw — OA Questions

**Day 0.** Questions shared from other institutes, with worked solutions in C++.

Three questions. Q1 is the only one with real difficulty — a greedy + heap
"repair" pattern. Q2 is DFS components + nC2. Q3 was a string-reversal variant.

**Contents**
- [Q1 — Maximum Negative PnL Days](#q1--maximum-negative-pnl-days)
- [Q2 — Tree with Two Zones, Add One Edge](#q2--tree-with-two-zones-add-one-edge)
- [Q3 — String Reversal (variant family)](#q3--string-reversal-variant-family)
- [Patterns worth carrying forward](#patterns-worth-carrying-forward)

---

## Q1 — Maximum Negative PnL Days

### Problem

Given an array `PnL` of `n` positive integers, where `PnL[i]` is the magnitude of
profit/loss on day `i`. For each index you choose a sign:

```
A[i] ∈ { PnL[i], -PnL[i] }
```

The resulting array must keep **every prefix sum strictly positive**:

```
sum(A[0..i]) > 0   for every 0 <= i < n
```

Maximize the number of negative elements.

### Key observations

1. **`A[0]` is forced positive.** The first prefix is just `A[0]`, so day 0 can
   never be negative.

2. **Repairing the past is always safe.** Flipping element `j` from `-x` to `+x`
   raises every prefix at index `>= j` by `2x` and leaves prefixes before `j`
   untouched. So undoing an earlier choice can never break a constraint that was
   already satisfied — it only ever helps.

3. **The obvious greedy is wrong.** "Make it negative whenever the running sum
   can afford it" fails, because a cheap early negative can block an expensive
   later one. The fix is to invert the greedy: be maximally negative, then repair
   only when forced.

### Strategy

Sweep left to right assuming *every* element is negative. Keep a max-heap of the
magnitudes currently marked negative.

- At each step: `S -= PnL[i]`, push `PnL[i]` onto the heap.
- While `S <= 0`: pop the **largest** magnitude and flip it back to positive
  (`S += 2 * x`).

Pop the largest because each flip costs exactly one negative, so you want the
flip that buys the most sum back — that minimizes the total number of flips.
Standard exchange argument.

Final answer = heap size = how many stayed negative.

The inner loop can never empty the heap: if everything were positive, `S` would
equal the sum of all magnitudes, which is `> 0`.

### Dry run

`PnL = [4, 2, 3, 1, 5]`

| i | val | S after `S -= val` | heap | action | S after | heap after |
|---|-----|--------------------|------|--------|---------|------------|
| 0 | 4 | `0 - 4 = -4` | {4} | `S <= 0` -> pop 4, `S += 8` | **4** | {} |
| 1 | 2 | `4 - 2 = 2` | {2} | ok | **2** | {2} |
| 2 | 3 | `2 - 3 = -1` | {3,2} | `S <= 0` -> pop 3, `S += 6` | **5** | {2} |
| 3 | 1 | `5 - 1 = 4` | {2,1} | ok | **4** | {2,1} |
| 4 | 5 | `4 - 5 = -1` | {5,2,1} | `S <= 0` -> pop 5, `S += 10` | **9** | {2,1} |

Heap size = 2 → **answer 2**.

Result: `[+4, -2, +3, -1, +5]`, prefixes `4, 2, 5, 4, 9` — all strictly
positive. ✓

**Why 3 is impossible:** day 0 is forced `+4`. From `{2, 3, 1, 5}` pick any 3 to
negate — all four choices fail:

| keep positive | array | prefixes |
|---|---|---|
| 5 | `+4, -2, -3, -1, +5` | `4, 2, -1` ✗ |
| 3 | `+4, -2, +3, -1, -5` | `4, 2, 5, 4, -1` ✗ |
| 2 | `+4, +2, -3, -1, -5` | `4, 6, 3, 2, -3` ✗ |
| 1 | `+4, -2, -3, +1, -5` | `4, 2, -1` ✗ |

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int maxNegativeDays(vector<long long>& PnL) {
    priority_queue<long long> negs;   // magnitudes currently held as negative
    long long S = 0;

    for (long long v : PnL) {
        S -= v;                       // optimistically make it negative
        negs.push(v);

        while (S <= 0) {              // prefix must be strictly positive
            long long x = negs.top(); negs.pop();
            S += 2 * x;               // -x becomes +x
        }
    }
    return (int)negs.size();          // whatever survived as negative
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;
    cout << maxNegativeDays(a) << "\n";
}
```

**Complexity:** O(n log n) time, O(n) space.

**Gotcha:** use `long long`. With `n = 1e5` values up to `1e9`, the running sum
overflows `int` immediately.

---

## Q2 — Tree with Two Zones, Add One Edge

### Problem

A tree with `n` nodes, each labelled zone 1 or zone 2. Add one edge between two
nodes; it is valid only if it connects two nodes of the **same zone**. Count how
many such edges can be added.

### Key reframing

Delete every tree edge whose endpoints are in different zones. What remains is a
forest where each component is a maximal blob of same-zone nodes. Then sum
`C(s, 2)` over the components.

### Read the statement carefully — two variants

| Reading | Answer | Needs DFS? |
|---|---|---|
| Any two nodes with the same zone *label* | `C(cnt1, 2) + C(cnt2, 2)` | No |
| Same zone **and** in the same connected same-zone region | `sum of C(s, 2)` | Yes |
| Same as above, but the edge must not already exist | `sum of C(s,2) - (s-1)` | Yes |

If the question needed DFS at all, it isn't the first reading. A tree component
of size `s` already contains `s - 1` edges, which is where the subtraction in the
third row comes from.

### Dry run

```
n = 7
zones:  1→A  2→A  3→B  4→A  5→B  6→B  7→A
edges:  1-2, 1-3, 2-4, 3-5, 3-6, 5-7

        1(A)
       /    \
     2(A)   3(B)
     /     /    \
   4(A)  5(B)   6(B)
          |
         7(A)
```

Cross-zone edges are `1-3` (A–B) and `5-7` (B–A). Cut them:

| component | nodes | size `s` | `C(s,2)` | `C(s,2) - (s-1)` |
|---|---|---|---|---|
| A-blob | {1, 2, 4} | 3 | 3 | 1 |
| B-blob | {3, 5, 6} | 3 | 3 | 1 |
| A-blob | {7} | 1 | 0 | 0 |

**Answer = 6** (all same-blob pairs), or **2** (new edges only).

Check the second column: in `{1,2,4}` the edges `1-2` and `2-4` already exist, so
`1-4` is the only genuinely new pair. Correct.

### Code — recursive

Clean and fine for `n` up to ~1e5 on a Linux judge.

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> graph;
vector<int> zone;
vector<bool> visited;
int cnt;

void dfs(int node) {
    visited[node] = true;
    cnt++;
    for (int nb : graph[node])
        if (!visited[nb] && zone[nb] == zone[node])   // never cross a zone
            dfs(nb);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    graph.resize(n + 1);
    zone.resize(n + 1);
    visited.resize(n + 1, false);

    for (int i = 1; i <= n; i++) cin >> zone[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;
        cnt = 0;
        dfs(i);
        ans += (long long)cnt * (cnt - 1) / 2;
        // new edges only:  ans -= (cnt - 1);
    }
    cout << ans << "\n";
}
```

**Complexity:** O(n) time and space.

**Gotchas:**

- Cast to `long long` *before* the multiply, not after. `cnt * (cnt-1) / 2` with
  `cnt = 1e5` is ~5e9 and overflows `int`.
- `visited.resize(n+1, false)` works only because the vector starts empty — the
  fill value applies to newly added elements only. Reusing a vector across test
  cases silently keeps the old contents.

### Code — iterative (large `n`)

A path-shaped same-zone tree gives `n` nested frames — roughly 6–8 MB of stack at
`n = 1e5`. Usually survives on Linux (8 MB default), dies on Windows (1 MB) or at
`n = 1e6`. Swap in the explicit stack when constraints are large:

```cpp
long long componentSize(int src) {
    long long sz = 0;
    stack<int> st;
    st.push(src); visited[src] = true;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        sz++;
        for (int v : graph[u])
            if (!visited[v] && zone[v] == zone[u]) {
                visited[v] = true;      // mark on PUSH, not on pop
                st.push(v);
            }
    }
    return sz;
}
```

Marking visited on push is the thing to get right — mark on pop and a node can
land on the stack twice and be counted twice.

---

## Q3 — String Reversal (variant family)

The exact statement wasn't captured — only that it was "reversal of a string,
brute force". Literal `reverse(s)` is never asked on its own, so below are the
standard variants it was most likely one of.

### 3.1 Reverse in place — the base pattern

Two pointers from the ends, swap inward. Every variant below is a mutation of
this.

```cpp
void reverseStr(string &s) {
    int i = 0, j = (int)s.size() - 1;
    while (i < j) swap(s[i++], s[j--]);
}
```

Dry run on `"abcde"`: `i=0,j=4` → `ebcda`; `i=1,j=3` → `edcba`; `i=2,j=2` stop.
Result **`edcba`**. O(n) time, O(1) space.

### 3.2 Reverse the order of words

`"  the sky  is blue  "` → `"blue is sky the"`. Leading/trailing/repeated spaces
are the whole trap.

```cpp
string reverseWords(string s) {
    vector<string> w;
    stringstream ss(s);
    string t;
    while (ss >> t) w.push_back(t);        // >> skips all whitespace runs
    reverse(w.begin(), w.end());
    string res;
    for (int i = 0; i < (int)w.size(); i++) {
        if (i) res += ' ';
        res += w[i];
    }
    return res;
}
```

Dry run: tokens `["the","sky","is","blue"]` → reversed `["blue","is","sky","the"]`
→ join → **`"blue is sky the"`**.

The `stringstream` tokenizing handles all the space cases for free. The O(1)-space
alternative — reverse the whole string, then reverse each word back while
compacting — is more impressive but slower to write correctly under time pressure.

### 3.3 Reverse each word, keep word order

`"God Ding"` → `"doG gniD"`.

```cpp
string reverseEachWord(string s) {
    int i = 0, n = s.size();
    while (i < n) {
        if (s[i] == ' ') { i++; continue; }
        int j = i;
        while (j < n && s[j] != ' ') j++;
        reverse(s.begin() + i, s.begin() + j);
        i = j;
    }
    return s;
}
```

Dry run on `"God Ding"`: segment `[0,3)` = `God` → `doG`; skip space; segment
`[4,8)` = `Ding` → `gniD`. Result **`"doG gniD"`**.

### 3.4 Reverse only certain characters (e.g. vowels)

Same two pointers, but each pointer skips non-target characters.

```cpp
string reverseVowels(string s) {
    auto isV = [](char c) {
        c = tolower((unsigned char)c);
        return c=='a'||c=='e'||c=='i'||c=='o'||c=='u';
    };
    int i = 0, j = s.size() - 1;
    while (i < j) {
        while (i < j && !isV(s[i])) i++;
        while (i < j && !isV(s[j])) j--;
        if (i < j) swap(s[i++], s[j--]);
    }
    return s;
}
```

Dry run on `"leetcode"`: vowels at indices 1(`e`), 2(`e`), 6(`o`). Swap 1↔6 →
`loetcede`; then `i=2, j=5`, `j` walks down to 2, loop ends. Result
**`"loetcede"`**.

Same skeleton solves "reverse only letters, leave punctuation in place" — just
change the predicate.

### 3.5 Reverse in groups of k

Reverse the first `k`, skip `k`, reverse the next `k`, … Partial tail is reversed
as-is.

```cpp
string reverseGroups(string s, int k) {
    int n = s.size();
    for (int i = 0; i < n; i += 2 * k)
        reverse(s.begin() + i, s.begin() + min(i + k, n));
    return s;
}
```

Dry run on `"abcdefg"`, `k=2`: `i=0` reverse `[0,2)` → `bacdefg`; `i=4` reverse
`[4,6)` → `bacdfeg`; `i=8` past end. Result **`"bacdfeg"`**.

The `min(i + k, n)` handles the ragged tail — omitting it is the classic bug.

### 3.6 Reverse substrings inside parentheses

`"(u(love)i)"` → `"iloveu"`. Stack of positions: on `(` push the current output
length, on `)` pop and reverse from there. Groups resolve inside-out
automatically.

```cpp
string reverseParentheses(string s) {
    string res;
    stack<int> st;
    for (char c : s) {
        if (c == '(') st.push(res.size());
        else if (c == ')') {
            reverse(res.begin() + st.top(), res.end());
            st.pop();
        } else res += c;
    }
    return res;
}
```

Dry run on `"(u(love)i)"`:

| char | action | res |
|---|---|---|
| `(` | push 0 | `""` |
| `u` | append | `"u"` |
| `(` | push 1 | `"u"` |
| `love` | append | `"ulove"` |
| `)` | pop 1, reverse from 1 | `"uevol"` |
| `i` | append | `"uevoli"` |
| `)` | pop 0, reverse from 0 | `"iloveu"` ✓ |

O(n²) worst case; O(n) with a precomputed jump-pair table if `n` is large.

### 3.7 Palindrome check — reversal as comparison

```cpp
bool isPal(const string &s) {
    int i = 0, j = s.size() - 1;
    while (i < j) if (s[i++] != s[j--]) return false;
    return true;
}
```

The interesting variant: **can it become a palindrome by deleting at most one
character?** On the first mismatch, try skipping the left char or the right char
and verify the remainder.

```cpp
bool palRange(const string &s, int i, int j) {
    while (i < j) if (s[i++] != s[j--]) return false;
    return true;
}

bool validPalindrome(const string &s) {
    int i = 0, j = s.size() - 1;
    while (i < j) {
        if (s[i] != s[j])
            return palRange(s, i + 1, j) || palRange(s, i, j - 1);
        i++; j--;
    }
    return true;
}
```

### 3.8 Minimum reversals to balance brackets

Often filed under "string reversal". Given `"}{{}}{{{"`, flip the fewest brackets
to balance the string.

Cancel matched pairs with a counter, leaving `m` unmatched `}` followed by `n`
unmatched `{`. Answer is `ceil(m/2) + ceil(n/2)`; impossible if the length is odd.

```cpp
int minReversals(const string &s) {
    if (s.size() % 2) return -1;
    int open = 0, unmatchedClose = 0;
    for (char c : s) {
        if (c == '{') open++;
        else { if (open) open--; else unmatchedClose++; }
    }
    return (unmatchedClose + 1) / 2 + (open + 1) / 2;
}
```

Dry run on `"}{{}}{{{"`: `}` → unmatchedClose=1; `{` → open=1; `{` → open=2;
`}` → open=1; `}` → open=0; `{{{` → open=3.
Result `(1+1)/2 + (3+1)/2 = 1 + 2 =` **3**.

---

## Patterns worth carrying forward

| Pattern | Where it showed up | Signal to watch for |
|---|---|---|
| Greedy + max-heap repair | Q1 | "maximize count subject to a running constraint" — take everything, undo the most expensive item when the constraint breaks |
| Prefix-sum monotonicity | Q1 | Undoing an earlier choice only helps later prefixes → greedy is safe |
| Component DFS + nC2 | Q2 | "connect any two nodes satisfying X" → cut invalid edges, count pairs per component |
| Two pointers inward | Q3, most variants | Any reversal / palindrome / swap-from-ends question |
| Stack of output positions | Q3.6 | Nested structure resolved inside-out |
