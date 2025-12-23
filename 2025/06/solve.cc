#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll solve1(const vector<ll>& ns, char op) {
    if (op == '+')
        return accumulate(ns.begin(), ns.end(), 0ll);
    if (op == '*')
        return accumulate(ns.begin(), ns.end(), 1ll,
                          [](ll v, ll w) { return v * w; });
    throw "error";
}

int main1() {
    string line;
    vector<vector<ll>> nums;
    vector<char> ops;

    bool first = true;
    while (getline(cin, line)) {
        istringstream ss(line);
        string tok;
        ll idx = 0;
        while (ss >> tok) {
            try {
                ll num = stoll(tok);
                if (first)
                    nums.push_back({num});
                else
                    nums[idx++].push_back(num);
            } catch (std::invalid_argument& e) {
                ops.push_back(tok[0]);
            }
        }
        first = false;
    }
    ll ret = 0;
    for (ll i = 0; i < ops.size(); ++i) {
        ret += solve1(nums[i], ops[i]);
    }
    cout << ret << endl;
    return 0;
}

ll solve2(const vector<string>& in, ll idx) {
    char op = in.back()[idx];
    ll ret = op == '+' ? 0 : 1;
    while (idx < in.back().size() &&
           (idx + 1 == in.back().size() || in.back()[idx + 1] == ' ')) {
        ll num = 0;
        for (ll i = 0; i + 1 < in.size(); ++i) {
            if (in[i][idx] != ' ')
                num = 10 * num + in[i][idx] - '0';
        }
        if (op == '+')
            ret += num;
        else
            ret *= num;
        idx++;
    }
    return ret;
}

int main() {
    vector<string> in;
    string line;
    while (getline(cin, line))
        in.push_back(std::move(line));

    ll ret = 0;
    for (ll i = 0; i < in.back().size(); ++i) {
        if (in.back()[i] != ' ')
            ret += solve2(in, i);
    }
    cout << ret << endl;
}
