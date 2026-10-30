/*#include <vector>
#include <iostream>
#include <queue>
using namespace std;
int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int n, m;
    cin>>n>>m;
    vector<string> v(n);
    pair<int, int> startpos = {-1, -1};

    for (int i = 0; i < n; i++) {
        cin >> v[i];
        size_t pos = v[i].find('S');
        if (pos != string::npos) {
            startpos = {i, static_cast<int>(pos)};
        }
    }

    queue<pair<pair<int,int>,int>> q;
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    q.emplace(startpos,0);
    visited[startpos.first][startpos.second] = true;

    int df[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    int ans=-1;
    while (!q.empty()) {
        auto [pos, steps] = q.front();
        q.pop();

        int r= pos.first;
        int c= pos.second;

        if (v[r][c] == 'E') {
            ans = steps;
        } else {
            for (int k = 0; k < 4; k++) {
                int nr = r + df[k];
                int nc = c + dc[k];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    if (!visited[nr][nc] && v[nr][nc] != '#') {
                        visited[nr][nc] = true;
                        q.emplace(make_pair(nr, nc), steps + 1);
                    }
                }
            }
        }
    }
    cout<<ans<<endl;

    return 0;
}*/