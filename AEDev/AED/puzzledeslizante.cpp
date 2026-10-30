/*#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int val=-1;
    string start = "";
    for (int i = 0; i < 6; i++) {
        char c;
        cin >> c;
        start += c;
    }

    string obj = "123450";
    if (start == obj) {
        val=0;
    } else {
        vector<vector<int>> posible = {{1, 3},{0, 2, 4},{1, 5},{0, 4},{1, 3, 5},{2, 4}};

        queue<pair<string, int>> q;
        unordered_set<string> seen;

        q.emplace(start, 0);
        seen.insert(start);

        while (!q.empty()) {
            auto [current, dist] = q.front();
            q.pop();

            if (current == obj) {
                val=dist;
            } else {
                int zero = current.find('0');

                for (int nextidx : posible[zero]) {
                    string next = current;
                    swap(next[zero], next[nextidx]);

                    if (seen.find(next) == seen.end()) {
                        seen.insert(next);
                        q.emplace(next, dist + 1);
                    }
                }
            }
        }
    }
    cout << val << "\n";

    return 0;
}*/