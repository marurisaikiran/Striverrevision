// CSES 1164 - Room Allocation
// Process by arrival; reuse the room that frees up earliest if it is free.
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<tuple<int, int, int>> c(n);     // (arrival, departure, index)
    for (int i = 0; i < n; i++) {
        auto& [a, b, id] = c[i];
        cin >> a >> b;
        id = i;
    }
    sort(c.begin(), c.end());
    // min-heap of (departure day, room number)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> busy;
    vector<int> room(n);
    int rooms = 0;
    for (auto [a, b, id] : c) {
        if (!busy.empty() && busy.top().first < a) {
            room[id] = busy.top().second;       // reuse the earliest-free room
            busy.pop();
        } else {
            room[id] = ++rooms;                 // every room is occupied
        }
        busy.push({b, room[id]});
    }
    cout << rooms << '\n';
    for (int i = 0; i < n; i++) cout << room[i] << (i + 1 < n ? ' ' : '\n');
    return 0;
}
