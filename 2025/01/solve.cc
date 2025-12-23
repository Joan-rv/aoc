#include <bits/stdc++.h>

using namespace std;

int main() {
    string line;
    int pos = 50;
    int res = 0;
    while (getline(cin, line)) {
        int ppos = pos;
        char dir = line[0];
        int move = stoi(line.substr(1));
        if (dir == 'L') {
            pos -= move;
            if (pos < 0)
                res += (-pos) / 100;
            if (pos <= 0 && ppos != 0)
                res++;
        } else {
            pos += move;
            res += pos / 100;
        }

        pos %= 100;
        if (pos < 0)
            pos += 100;
    }
    cout << res << endl;
}
