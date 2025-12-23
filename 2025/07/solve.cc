#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    vector<string> grid;
    string line;
    while (getline(cin, line))
        grid.push_back(line);

    vector<vector<ll>> dp(grid.size(), vector<ll>(grid[0].size(), 0));
    for (ll i = 0; i + 1 < grid.size(); ++i) {
        for (ll j = 0; j < grid[i].size(); ++j) {
            if (grid[i + 1][j] == '.' || grid[i + 1][j] == '|') {
                grid[i + 1][j] = '|';
                dp[i + 1][j] += grid[i][j] == 'S' ? 1 : dp[i][j];
            } else if (grid[i + 1][j] == '^') {
                grid[i + 1][j - 1] = '|';
                dp[i + 1][j - 1] += dp[i][j];
                grid[i + 1][j + 1] = '|';
                dp[i + 1][j + 1] += dp[i][j];
            }
        }
    }
    cout << accumulate(dp.back().begin(), dp.back().end(), 0ll) << endl;
}
