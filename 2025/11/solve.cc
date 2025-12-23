#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

map<string, vector<string>> G;

ll ret = 0;

void dfs(const string& u) {
    if (u == "out") {
        ret++;
        return;
    }
    for (auto&& v : G[u])
        dfs(v);
}

map<tuple<string, bool, bool>, ll> cache;
ll dfs(const string& u, bool dac, bool fft) {
    if (cache.find({u, dac, fft}) != cache.end())
        return cache[{u, dac, fft}];
    if (u == "out") {
        if (dac && fft)
            return 1;
        return 0;
    }
    ll ret = 0;
    for (auto&& v : G[u]) {
        if (v == "dac") {
            ret += dfs(v, true, fft);
        } else if (v == "fft") {
            ret += dfs(v, dac, true);
        } else {
            ret += dfs(v, dac, fft);
        }
    }
    return cache[{u, dac, fft}] = ret;
}

int main() {
    string line;
    while (getline(cin, line)) {
        istringstream ss(line);
        string u;
        ss >> u;
        u = u.substr(0, u.size() - 1);
        string v;
        while (ss >> v) {
            G[u].push_back(v);
        }
    }
    // dfs("you")
    ret = dfs("svr", false, false);
    cout << ret << endl;
}
