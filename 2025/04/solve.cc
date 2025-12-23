#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0},  {-1, 0},
                               {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

vector<string> grid;
int n, m;

bool pos_ok(int i, int j) { return i >= 0 && j >= 0 && i < n && j < m; }

bool solve(int i, int j) {
    if (grid[i][j] != '@')
        return false;
    int c = 0;
    for (auto dir : dirs) {
        int i2 = i + dir.first;
        int j2 = j + dir.second;
        if (!pos_ok(i2, j2))
            continue;
        if (grid[i2][j2] == '@')
            c++;
    }
    return c < 4;
}

int main() {
    string line;
    while (getline(cin, line)) {
        grid.push_back(line);
    }
    n = grid.size();
    m = grid[0].size();
    int ret = 0;
    vector<pair<int, int>> remd;
    do {
        for (auto [i, j] : remd) {
            grid[i][j] = '.';
        }
        remd.clear();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (solve(i, j)) {
                    remd.push_back({i, j});
                    ret++;
                }
            }
        }
    } while (!remd.empty());

    cout << ret << endl;
}
