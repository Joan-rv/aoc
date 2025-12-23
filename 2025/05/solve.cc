#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool is_fresh(ll id, const vector<pair<ll, ll>>& ranges) {
    for (auto [l, r] : ranges) {
        if (l <= id && id <= r)
            return true;
    }
    return false;
}

vector<pair<ll, ll>> range_merge(const vector<pair<ll, ll>>& ranges) {
    int idx = 0;
    vector<pair<ll, ll>> ret;
    while (idx < ranges.size()) {
        auto [l, r] = ranges[idx++];
        while (idx < ranges.size() && ranges[idx].first <= r) {
            r = max(r, ranges[idx++].second);
        }
        ret.push_back({l, r});
    }
    return ret;
}

ll solve2(const vector<pair<ll, ll>>& ranges) {
    ll ret = 0;
    for (auto [l, r] : ranges)
        ret += r - l + 1;
    return ret;
}

int main() {
    vector<pair<ll, ll>> ranges;
    vector<ll> ids;
    string line;
    while (getline(cin, line)) {
        if (line == "")
            break;
        ll pos = line.find('-');
        ll l = stoll(line.substr(0, pos));
        ll r = stoll(line.substr(pos + 1));
        ranges.push_back({l, r});
    }
    while (getline(cin, line)) {
        ids.push_back(stoll(line));
    }
    sort(ranges.begin(), ranges.end());
    ll ret = 0;
    for (auto id : ids) {
        if (is_fresh(id, ranges))
            ret++;
    }
    cout << ret << endl;
    ranges = range_merge(ranges);
    cout << solve2(ranges) << endl;
}
