#include <iostream>
#include <vector>

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
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

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int makeConnected(int n, std::vector<std::vector<int>>& connections) {
    int totalConnections = n * (n - 1) / 2;
    if (connections.size() > std::min(totalConnections, 100'000)) {
        return -1;
    }

    UnionFind uf(n);
    int extraCables = 0;

    for (const auto& conn : connections) {
        int u = conn[0];
        int v = conn[1];
        if (uf.find(u) != uf.find(v)) {
            uf.unionSets(u, v);
        } else {
            extraCables++;
        }
    }

    int components = 0;
    for (int i = 0; i < n; ++i) {
        if (uf.find(i) == i) {
            components++;
        }
    }

    return extraCables >= components - 1 ? components - 1 : -1;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> connections = {{0, 1}, {0, 2}, {1, 2}};
    int result = makeConnected(n, connections);
    std::cout << result << std::endl;

    return 0;
}
