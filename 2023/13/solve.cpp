#include <bits/stdc++.h>

using namespace std;

using ll = long long;

vector<string> read_tiles() {
    string line;
    vector<string> tiles;
    while (getline(cin, line)) {
        if (line.empty())
            break;
        tiles.push_back(std::move(line));
    }
    return tiles;
}

ll find_reflection(const vector<string>& tiles) {
    ll n = tiles.size();
    ll m = tiles[0].size();
    for (ll j = 0; j + 1 < m; j++) {
        bool is_reflection = true;
        for (ll c1 = 0; c1 <= j && is_reflection; c1++) {
            ll c2 = j + (j - c1 + 1);
            if (c2 >= m)
                continue;
            for (ll i = 0; i < n && is_reflection; i++) {
                is_reflection = tiles[i][c1] == tiles[i][c2];
            }
        }
        if (is_reflection)
            return j + 1;
    }
    for (ll i = 0; i + 1 < n; i++) {
        bool is_reflection = true;
        for (ll r1 = 0; r1 <= i && is_reflection; r1++) {
            ll r2 = i + (i - r1 + 1);
            if (r2 >= n)
                continue;
            for (ll j = 0; j < m && is_reflection; j++) {
                is_reflection = tiles[r1][j] == tiles[r2][j];
            }
        }
        if (is_reflection)
            return (i + 1) * 100;
    }
    return 0;
}

ll find_smudge(const vector<string>& tiles) {
    ll n = tiles.size();
    ll m = tiles[0].size();
    for (ll j = 0; j + 1 < m; j++) {
        ll wrong_tiles = 0;
        for (ll c1 = 0; c1 <= j; c1++) {
            ll c2 = j + (j - c1 + 1);
            if (c2 >= m)
                continue;
            for (ll i = 0; i < n; i++) {
                wrong_tiles += tiles[i][c1] != tiles[i][c2];
            }
        }
        if (wrong_tiles == 1)
            return j + 1;
    }
    for (ll i = 0; i + 1 < n; i++) {
        ll wrong_tiles = 0;
        for (ll r1 = 0; r1 <= i; r1++) {
            ll r2 = i + (i - r1 + 1);
            if (r2 >= n)
                continue;
            for (ll j = 0; j < m; j++) {
                wrong_tiles += tiles[r1][j] != tiles[r2][j];
            }
        }
        if (wrong_tiles == 1)
            return (i + 1) * 100;
    }
    return 0;
}

int main() {
    ll res = 0;
    while (!cin.eof()) {
        auto tiles = read_tiles();
        // res += find_reflection(tiles);
        res += find_smudge(tiles);
    }
    cout << res << endl;
}
