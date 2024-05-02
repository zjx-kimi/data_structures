#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <vector>
#include <iostream>
#define pii pair <int, int>
#define all(a) a.begin(), a.end();
using namespace std;

// 树状数组
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

// 线段树
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

// DSU
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

#endif // DATA_STRUCTURES_H
