#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using Tile = vector<string>;

struct Region {
    ll n, m;
    vector<int> freqs;
};

Tile read_tile() {
    string line;
    Tile t;
    while (getline(cin, line)) {
        if (line.empty())
            break;
        t.push_back(line);
    }
    return t;
}

vector<Tile> ts;
vector<string> G;

bool can_place(const Tile& t, int i, int j) {
    if (i < 0 || j < 0 || i > G.size() - 3 || j > G[0].size() - 3)
        return false;
    for (int i2 = 0; i2 < t.size(); ++i2) {
        for (int j2 = 0; j2 < t[0].size(); ++j2) {
            if (t[i2][j2] == '#' && G[i + i2][j + j2] == '#')
                return false;
        }
    }
    return true;
}

void place_tile(const Tile& t, int i, int j) {
    for (int i2 = 0; i2 < t.size(); ++i2) {
        for (int j2 = 0; j2 < t[0].size(); ++j2) {
            if (t[i2][j2] == '#')
                G[i + i2][j + j2] = '#';
        }
    }
}
void unplace_tile(const Tile& t, int i, int j) {
    for (int i2 = 0; i2 < t.size(); ++i2) {
        for (int j2 = 0; j2 < t[0].size(); ++j2) {
            if (t[i2][j2] == '#')
                G[i + i2][j + j2] = '.';
        }
    }
}

void rot_tile(Tile& t) {
    assert(t.size() == t[0].size());
    auto r = t;
    for (int i = 0; i < t.size(); ++i) {
        for (int k = 0; k < t.size(); ++k)
            r[k][t.size() - i - 1] = t[i][k];
    }
    t = r;
}

void flip_tile(Tile& t) {
    for (int i = 0; i < t.size(); ++i) {
        for (int j = 0; j < t[0].size() / 2; ++j) {
            swap(t[i][j], t[i][t[0].size() - j - 1]);
        }
    }
}

bool solve(Region& r, int i0, int j0) {
    bool all_zero = true;
    for (int l = 0; l < r.freqs.size(); ++l) {
        if (r.freqs[l] == 0)
            continue;
        all_zero = false;
        auto t = ts[l];
        for (int k = 0; k < 4; ++k) {
            for (int i = 1; i <= 5; ++i) {
                for (int j = 1; j <= 5; ++j) {
                    if (can_place(t, i0 + i, j0 + j)) {
                        r.freqs[l]--;
                        place_tile(t, i0 + i, j0 + j);
                        if (solve(r, i0 + i, j0 + j))
                            return true;
                        unplace_tile(t, i0 + i, j0 + j);
                        r.freqs[l]++;
                    }
                }
            }
            rot_tile(t);
        }
        flip_tile(t);
        for (int k = 0; k < 4; ++k) {
            for (int i = 1; i <= 5; ++i) {
                for (int j = 1; j <= 5; ++j) {
                    if (can_place(t, i0 + i, j0 + j)) {
                        r.freqs[l]--;
                        place_tile(t, i0 + i, j0 + j);
                        if (solve(r, i0 + i, j0 + j))
                            return true;
                        unplace_tile(t, i0 + i, j0 + j);
                        r.freqs[l]++;
                    }
                }
            }
            rot_tile(t);
        }
    }
    return all_zero;
}

bool solve(Region& r) { // return solve(r, -1, -1);
    int sum = 0;
    for (auto f : r.freqs)
        sum += f;
    if (sum * 9 <= r.n * r.m)
        return true;
    else
        return false;
}

int main() {
    string line;
    while (getline(cin, line)) {
        if ('0' <= line[0] && line[0] <= '9' && line[1] == ':')
            ts.push_back(read_tile());
        else
            break;
    }
    vector<Region> rs;
    do {
        Region r;
        istringstream ss(line);
        string dims;
        ss >> dims;
        r.n = stoll(dims.substr(0, dims.find('x')));
        r.m = stoll(dims.substr(dims.find('x') + 1, dims.size() - 1));
        ll x;
        while (ss >> x)
            r.freqs.push_back(x);
        rs.push_back(r);
    } while (getline(cin, line));
    ll ret = 0;
    for (auto& r : rs) {
        G.assign(r.n, string(r.m, '.'));
        if (solve(r)) {
            ret++;
        }
    }
    cout << ret << endl;
}
