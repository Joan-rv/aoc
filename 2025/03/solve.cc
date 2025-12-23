#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll joltage(const string& line) {
    vector<ll> ds(12, -1);
    vector<size_t> ps(12, 0);
    for (int i = 0; i < 12; ++i) {
        for (size_t j = i == 0 ? 0 : ps[i - 1] + 1; j < line.size() - 11 + i;
             ++j) {
            if (ds[i] < line[j] - '0') {
                ds[i] = line[j] - '0';
                ps[i] = j;
            }
        }
    }
    ll ret = 0;
    for (int i = 0; i < 12; ++i) {
        ret = ret * 10 + ds[i];
    }
    return ret;
}

int main() {
    string line;
    ll sum = 0;
    while (getline(cin, line)) {
        sum += joltage(line);
    }
    cout << sum << endl;
}
