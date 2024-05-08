#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include <queue>
#include <stack>
#include <vector>
#include <iostream>
#define pii pair <int, int>
#define all(a) a.begin(), a.end();
using namespace std;
int max(int count, ...) {
    va_list args;
    va_start(args, count);

    int maxVal = va_arg(args, int);
    for (int i = 1; i < count; ++i) {
        int val = va_arg(args, int);
        if (val > maxVal) {
            maxVal = val;
        }
    }

    va_end(args);
    return maxVal;
}
int min(int count, ...) {
    va_list args;
    va_start(args, count);

    int minVal = va_arg(args, int);
    for (int i = 1; i < count; ++i) {
        int val = va_arg(args, int);
        if (val < maxVal) {
            minVal = val;
        }
    }

    va_end(args);
    return minVal;
}
struct FenwickTree {
    vector<int> tree;

    FenwickTree(int n) : tree(n + 1) {}

    void update(int idx, int val) {
        while (idx < tree.size()) {
            tree[idx] += val;
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
};
struct SegmentTree {
    vector<int> tree;

    SegmentTree(int n) {
        int sz = 1;
        while (sz < n) sz *= 2;
        tree.assign(2 * sz, 0);
    }

    void update(int idx, int val, int node, int node_left, int node_right) {
        if (node_left == node_right) {
            tree[node] = val;
            return;
        }
        int mid = (node_left + node_right) / 2;
        if (idx <= mid) {
            update(idx, val, 2 * node, node_left, mid);
        } else {
            update(idx, val, 2 * node + 1, mid + 1, node_right);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void update(int idx, int val, int n) {
        update(idx, val, 1, 0, n - 1);
    }

    int query(int left, int right, int node, int node_left, int node_right) {
        if (right < node_left || left > node_right) return 0;
        if (left <= node_left && right >= node_right) return tree[node];
        int mid = (node_left + node_right) / 2;
        return query(left, right, 2 * node, node_left, mid) +
               query(left, right, 2 * node + 1, mid + 1, node_right);
    }

    int query(int left, int right, int n) {
        return query(left, right, 1, 0, n - 1);
    }
};
struct DSU {
    vector<int> parent;

    DSU(int n) : parent(n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }
};

#endif
