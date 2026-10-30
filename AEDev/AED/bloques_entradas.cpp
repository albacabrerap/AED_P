/*#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    unordered_set<int> seen;
    int groups = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (seen.count(x)) {
            cout << groups << " ";
        } else {
            bool left = seen.count(x - 1);
            bool right = seen.count(x + 1);

            if (left && right) {
                groups--;
            } else if (!left && !right) {
                groups++;
            }

            seen.insert(x);
            cout << groups << " ";
        }
    }

    return 0;
}*/