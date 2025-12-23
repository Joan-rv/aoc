#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void roll_north_rock(vector<string>& map, int i, int j) {
    while (i > 0 && map[i - 1][j] == '.') {
        map[i][j] = '.';
        map[i - 1][j] = 'O';
        i--;
    }
}

void roll_north(vector<string>& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == 'O')
                roll_north_rock(map, i, j);
        }
    }
}

void roll_east_rock(vector<string>& map, int i, int j) {
    while (j + 1 < map[0].size() && map[i][j + 1] == '.') {
        map[i][j] = '.';
        map[i][j + 1] = 'O';
        ++j;
    }
}

void roll_east(vector<string>& map) {
    for (int j = map[0].size() - 1; j >= 0; j--) {
        for (int i = 0; i < map.size(); i++) {
            if (map[i][j] == 'O')
                roll_east_rock(map, i, j);
        }
    }
}
void roll_south_rock(vector<string>& map, int i, int j) {
    while (i + 1 < map.size() && map[i + 1][j] == '.') {
        map[i][j] = '.';
        map[i + 1][j] = 'O';
        i++;
    }
}

void roll_south(vector<string>& map) {
    for (int i = map.size() - 1; i >= 0; i--) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == 'O')
                roll_south_rock(map, i, j);
        }
    }
}
void roll_west_rock(vector<string>& map, int i, int j) {
    while (j > 0 && map[i][j - 1] == '.') {
        map[i][j] = '.';
        map[i][j - 1] = 'O';
        --j;
    }
}

void roll_west(vector<string>& map) {
    for (int j = 0; j < map[0].size(); j++) {
        for (int i = 0; i < map.size(); i++) {
            if (map[i][j] == 'O')
                roll_west_rock(map, i, j);
        }
    }
}

ll total_load(vector<string>& map) {
    ll load = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == 'O')
                load += map.size() - i;
        }
    }
    return load;
}

void print_map(vector<string>& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            cout << map[i][j];
        }
        cout << '\n';
    }
    cout << '\n';
}

int main() {
    vector<string> map;
    string line;
    while (getline(cin, line)) {
        map.push_back(line);
    }

    vector<vector<string>> prevs = {map};
    for (ll i = 0; i < 1000000000; i++) {
        roll_north(map);
        roll_west(map);
        roll_south(map);
        roll_east(map);
        // print_map(map);
        auto f = prevs.rend();
        if ((f = find(prevs.rbegin(), prevs.rend(), map)) != prevs.rend()) {
            ll c_len = f - prevs.rbegin() + 1;
            cout << "cycle of: " << c_len << endl;
            i += c_len * ((999999999 - i) / c_len);
        } else {
            prevs.push_back(map);
        }
    }
    /*
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            cout << map[i][j];
        }
        cout << '\n';
    }
    */
    cout << total_load(map) << endl;
    return 0;
}
