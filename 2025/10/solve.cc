#include <bits/stdc++.h>
#include <z3++.h>

using namespace std;

typedef long long ll;

ll solve(uint32_t target, const vector<uint32_t>& transitions,
         const vector<ll>& jolts) {
    uint32_t state_max = 1 << jolts.size();
    vector<ll> dp(state_max, LLONG_MAX);
    vector<bool> vis(state_max, false);
    dp[0] = 0;
    while (true) {
        ll idx = -1;
        for (ll i = 0; i < dp.size(); ++i) {
            if (vis[i])
                continue;
            if (idx == -1 || dp[i] < dp[idx])
                idx = i;
        }
        if (idx == -1)
            break;
        vis[idx] = true;
        for (auto t : transitions) {
            dp[t ^ idx] = min(dp[t ^ idx], 1 + dp[idx]);
        }
    }
    return dp[target];
}

void print(const vector<valarray<ll>>& M) {
    for (const auto& r : M) {
        for (auto&& v : r)
            cout << v << ' ';
        cout << endl;
    }
    cout << endl;
}

void sort_leading_zeros(vector<valarray<ll>>& M) {
    sort(M.begin(), M.end(),
         [](const valarray<ll>& v1, const valarray<ll>& v2) {
             ll n1 = 0;
             for (ll i = 0; i < v1.size(); ++i)
                 if (v1[i] == 0)
                     n1++;
                 else
                     break;
             ll n2 = 0;
             for (ll i = 0; i < v2.size(); ++i)
                 if (v2[i] == 0)
                     n2++;
                 else
                     break;
             return n1 < n2;
         });
}

vector<ll> gauss(vector<valarray<ll>>& M) {
    ll n = M.size();
    ll m = M[0].size();
    for (ll i = 0; i < n; ++i) {
        for (ll j = i + 1; j < n; ++j) {
            if (M[j][i] != 0) {
                M[j] = M[j] - M[i] * M[j][i] / M[i][i];
            }
        }
        sort_leading_zeros(M);
    }
    ll r = 0;
    for (ll i = 0; i < n; ++i)
        if (M[i].max() == 0)
            break;
        else
            r++;
    print(M);
    if (r == m - 1) {
        vector<ll> sol(m - 1, 0);
        for (ll i = m - 2; i >= 0; --i) {
            ll val = M[i][m - 1];
            for (ll j = m - 2; j > i; --j)
                val -= sol[j] * M[i][j];
            sol[i] = M[i][m - 1] / M[i][i];
        }
        return sol;
    } else {
        vector<valarray<ll>> basis(m - 1 - r + 1, valarray<ll>(m - 1));
        for (ll i = 0; i < r; ++i) {
            ll idx = 0;
            while (M[i][idx] == 0)
                idx++;
            basis[0][idx] = M[i][m - 1];
        }
        for (ll i = 0; i < r; ++i) {
        }
    }
    return {};
}

ll solve2(const vector<vector<bool>>& trans, vector<ll>& state,
          const vector<ll>& tgt, ll cost) {
    z3::context ctx;
    z3::optimize opt(ctx);
    int n = trans.size();
    vector<z3::expr> vars;
    for (int i = 0; i < n; ++i) {
        vars.push_back(ctx.int_const(("x" + std::to_string(i)).c_str()));
        opt.add(vars[i] >= 0);
    }
    z3::expr sum = vars[0];
    for (int i = 1; i < n; ++i) {
        sum = sum + vars[i];
    }
    opt.minimize(sum);
    for (int i = 0; i < tgt.size(); ++i) {
        z3::expr eq = vars[0] * 0;
        for (int j = 0; j < trans.size(); ++j) {
            if (trans[j][i])
                eq = eq + vars[j];
        }
        eq = eq == ctx.int_val((int64_t)tgt[i]);
        opt.add(eq);
    }
    ll ret = 0;
    if (opt.check() == z3::sat) {
        z3::model m = opt.get_model();
        for (int i = 0; i < m.size(); ++i) {
            auto v = m.get_const_decl(i);
            ret += m.get_const_interp(v).get_numeral_int();
        }
    }
    return ret;
}

ll solve2(uint32_t target, const vector<uint32_t>& transitions,
          const vector<ll>& jolts) {
    vector<vector<bool>> trans;
    for (ll i = 0; i < transitions.size(); ++i) {
        vector<bool> t(jolts.size());
        for (ll j = 0; j < jolts.size(); ++j)
            t[j] = ((transitions[i] & (1 << j)) == 0) ? 0 : 1;
        trans.push_back(t);
    }
    auto state = vector<ll>(jolts.size(), 0);
    return solve2(trans, state, jolts, 0ll);
}

int main() {
    string line;
    vector<uint32_t> lights;
    vector<vector<uint32_t>> toggles;
    vector<vector<ll>> jolts;
    while (getline(cin, line)) {
        vector<uint32_t> toggle;
        istringstream ss(line);
        string word;
        while (ss >> word) {
            if (word[0] == '[') {
                uint32_t light = 0;
                for (int i = 1; i + 1 < word.size(); ++i) {
                    if (word[i] == '#')
                        light |= 1 << (i - 1);
                }
                lights.push_back(light);
            } else if (word[0] == '(') {
                uint32_t t = 0;
                for (int i = 1; i + 1 < word.size(); ++i) {
                    if (word[i] != ',')
                        t |= 1 << (word[i] - '0');
                }
                toggle.push_back(t);
            } else if (word[0] == '{') {
                vector<ll> jolt;
                istringstream sss(word.substr(1));
                ll j;
                char tmp;
                while (sss >> j >> tmp)
                    jolt.push_back(j);
                jolts.push_back(jolt);
            }
        }
        toggles.push_back(toggle);
    }

    ll ret = 0;
    for (int i = 0; i < lights.size(); ++i) {
        cerr << '\r' << setw(5) << i + 1 << '/' << lights.size();
        ret += solve2(lights[i], toggles[i], jolts[i]);
    }
    cout << endl << ret << endl;
}
