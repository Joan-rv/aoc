#include <bits/stdc++.h>

using namespace std;

struct Pt {
    long x, y, z;
    bool operator==(const Pt b) const {
        return x == b.x && y == b.y && z == b.z;
    }
};

long dist(Pt a, Pt b) {
    long dx = a.x - b.x;
    long dy = a.y - b.y;
    long dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

vector<Pt>& find_circuit(vector<vector<Pt>>& circuits, Pt box) {
    for (auto& circuit : circuits) {
        if (find(circuit.begin(), circuit.end(), box) != circuit.end())
            return circuit;
    }
    assert(false);
}

int main() {
    string line;
    vector<Pt> boxes;
    while (getline(cin, line)) {
        Pt p;
        char tmp;
        istringstream ss(line);
        ss >> p.x >> tmp >> p.y >> tmp >> p.z;
        boxes.push_back(p);
    }
    vector<vector<Pt>> circuits;
    for (long i = 0; i < boxes.size(); ++i)
        circuits.push_back({boxes[i]});
    vector<pair<long, int>> pairs;
    for (long i = 0; i < boxes.size(); ++i) {
        for (long j = i + 1; j < boxes.size(); ++j)
            pairs.push_back({i, j});
    }
    sort(pairs.begin(), pairs.end(), [&boxes](auto a, auto b) {
        return dist(boxes[a.first], boxes[a.second]) <
               dist(boxes[b.first], boxes[b.second]);
    });
    int idx = 0;
    while (1) {
        auto [i, j] = pairs[idx++];
        Pt b1 = boxes[i], b2 = boxes[j];
        auto& c1 = find_circuit(circuits, b1);
        auto& c2 = find_circuit(circuits, b2);
        if (&c1 == &c2)
            continue;
        for (auto b : c2)
            c1.push_back(b);
        c2.clear();
        if (c1.size() == boxes.size()) {
            cout << b1.x * b2.x << endl;
            exit(0);
        }
    }
}
