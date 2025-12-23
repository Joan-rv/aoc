#include <bits/stdc++.h>

using namespace std;

struct Pt {
    long x, y;
    bool operator<(Pt b) const { return x != b.x ? x < b.x : y < b.y; }
};

struct Seg {
    long c;
    long c0, cf;
    bool operator<(const Seg& o) const {
        return c != o.c ? c < o.c : c0 != o.c0 ? c0 < o.c0 : cf < o.cf;
    }
};

vector<Seg> x_segs;
vector<Seg> y_segs;

bool is_valid(const Pt& a, const Pt& b) {
    // m--------my
    // |        |
    // mx------ M
    Pt m = {min(a.x, b.x), min(a.y, b.y)};
    Pt M = {max(a.x, b.x), max(a.y, b.y)};
    Pt mx = {min(a.x, b.x), max(a.y, b.y)};
    Pt my = {max(a.x, b.x), min(a.y, b.y)};

    for (auto& s : y_segs) {
        if (max(s.c0, m.x) < min(s.cf, M.x)) {
            if (s.c < M.y && s.c > m.y)
                return false;
        }
    }
    for (auto& s : x_segs) {
        if (max(s.c0, m.y) < min(s.cf, M.y)) {
            if (s.c < M.x && s.c > m.x)
                return false;
        }
    }
    return true;
}

int main() {
    string line;
    vector<Pt> ps;
    while (getline(cin, line)) {
        char tmp;
        istringstream ss(line);
        Pt p;
        ss >> p.x >> tmp >> p.y;
        ps.push_back(p);
    }

    for (int i = 0; i < ps.size(); ++i) {
        Pt p = ps[i], q = ps[(i + 1) % ps.size()];
        if (p.x != q.x)
            y_segs.push_back({p.y, min(p.x, q.x), max(p.x, q.x)});
        else
            x_segs.push_back({p.x, min(p.y, q.y), max(p.y, q.y)});
    }

    long M = 0;
    for (long i = 0; i < ps.size(); ++i) {
        std::cerr << '\r' << setw(5) << i << "/" << setw(5) << ps.size();
        for (long j = i + 1; j < ps.size(); ++j) {
            Pt p = ps[i];
            Pt q = ps[j];
            long a = (abs(p.x - q.x) + 1) * (abs(p.y - q.y) + 1);
            if (a < M)
                continue;
            if (!is_valid(p, q))
                continue;
            if (a > M) {
                M = a;
            }
        }
    }
    cout << endl << M << endl;
}
