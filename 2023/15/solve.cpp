#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll ini_hash(string& str) {
    uint8_t h = 0;
    for (char c : str) {
        h += c;
        h *= 17;
    }
    return h;
}

int main() {
    string ins;
    ll sum = 0;
    while (getline(cin, ins, ',')) {
        if (ins.back() == '\n')
            ins.pop_back();
        sum += ini_hash(ins);
    }
    cout << sum << endl;
    return 0;
}
