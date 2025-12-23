#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll powll(ll x, ll y) {
    if (y == 0)
        return 1;
    ll z = powll(x, y / 2);
    if (y % 2 == 0)
        return z * z;
    else
        return x * z * z;
}

ll solve(string min, string max) {
    ll ret = 0;
    int l_start = min.size();
    ll half_start;
    if (l_start != 1) {
        half_start = stoll(min.substr(0, l_start / 2));
        if (half_start < stoll(min.substr(l_start / 2)))
            half_start++;
    }
    if (l_start % 2 == 1) {
        half_start = powll(10, l_start / 2);
        l_start++;
    }
    int l_end = max.size();
    ll half_end;
    if (l_end != 1) {
        half_end = stoll(max.substr(0, l_end / 2));
        if (half_end > stoll(max.substr(l_end / 2))) {
            half_end--;
        }
    }
    if (l_end % 2 == 1)
        half_end = powll(10, l_end);

    for (int l = l_start; l <= l_end; l += 2) {
        ll p = powll(10, l / 2);
        for (int half = half_start; half <= half_end && half < p; half++) {
            ret += half + half * p;
        }
        half_start = p;
    }
    return ret;
}

bool has_smaller(ll x, ll n) {
    for (int i = 1; i < n; ++i) {
        if (n % i != 0)
            continue;
        ll p = powll(10, i);
        bool all_equal = true;
        ll y = x % p;
        for (int j = i; j < n && all_equal; j += i) {
            if ((x / powll(10, j)) % p != y)
                all_equal = false;
        }
        if (all_equal)
            return true;
    }
    return false;
}

ll solve2(const string& min, const string& max, int n = 1) {
    if (2 * n > max.size())
        return 0;
    ll ret = 0;
    ret += solve2(min, max, n + 1);
    int l_start = min.size();
    ll x_start = powll(10, n - 1);
    if (min.size() % n == 0) {
        x_start = stoll(min.substr(0, n));
        for (int i = n; i < min.size(); i += n) {
            if (x_start > stoll(min.substr(i, n)))
                break;
            if (x_start < stoll(min.substr(i, n))) {
                x_start++;
                break;
            }
        }
    }
    int l_end = max.size();
    ll x_end = powll(10, n) - 1;
    if (max.size() % n == 0) {
        x_end = stoll(max.substr(0, n));
        for (int i = n; i < max.size(); i += n) {
            if (x_end < stoll(max.substr(i, n)))
                break;
            if (x_end > stoll(max.substr(i, n))) {
                x_end--;
                break;
            }
        }
    }

    for (int i = std::max(2 * n, ((l_start + n - 1) / n) * n); i <= l_end;
         i += n) {
        ll stop = i == l_end ? x_end : powll(10, n) - 1;
        for (int x = x_start; x <= stop; ++x) {
            if (has_smaller(x, n))
                continue;
            for (int j = 0; j < i; j += n)
                ret += x * powll(10, j);
        }
        x_start = powll(10, n - 1);
    }

    return ret;
}

int main() {
    std::string line;
    getline(cin, line);
    size_t pos;
    ll res = 0;
    while ((pos = line.find(',')) != std::string::npos) {
        auto range = line.substr(0, pos);
        line.erase(0, pos + 1);
        size_t pos2 = range.find('-');
        auto start = range.substr(0, pos2);
        auto end = range.substr(pos2 + 1);
        res += solve2(start, end);
    }
    auto range = line;
    size_t pos2 = range.find('-');
    auto start = range.substr(0, pos2);
    auto end = range.substr(pos2 + 1);
    res += solve2(start, end);
    cout << res << endl;
}
