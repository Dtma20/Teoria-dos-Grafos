#include <bits/stdc++.h>
using namespace std;

vector<int> parent(100001), ranks(100001, 0);

void make_set(int v) {
    parent[v] = v;
    ranks[v] = 0;
}
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (ranks[a] < ranks[b])
            swap(a, b);
        parent[b] = a;
        if (ranks[a] == ranks[b])
            ranks[a]++;
    }
}
int main() {
    for(int i = 0; i < parent.size(); i++) {
        make_set(i);
    }
    union_sets(1, 2);
    union_sets(2, 3);
    union_sets(3, 4);
    cout << find_set(2) << endl;
    return 0;
}
