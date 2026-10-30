#include <vector>
#include <iostream>
#include <queue>
using namespace std;
int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int n, m;
    cin>>n>>m;

    vector<string> v(n+1);
    pair<int, int> startpos = {1, 1};

    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        v[i]=' '+v[i]+' ';
    }

    deque<pair<int,int>> q;
    vector<vector<int>> dis(n+1, vector<int>(m+1, -1));

    q.push_front(startpos);
    dis[startpos.first][startpos.second] =0;

    int df[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    int ans=0;
    while (!q.empty()) {
        {
            auto [r, c] = q.front();
            q.pop_front();

            if (r==n && c==m) {
                ans = dis[r][c];
            } else {
                for (int k = 0; k < 4; k++) {
                    int nr = r + df[k];
                    int nc = c + dc[k];

                    if (nr >= 1 && nr <= n && nc >= 1 && nc <= m) {
                        if (int wall=v[nr][nc] == '#' ? 1 : 0; dis[nr][nc]>dis[r][c]+wall || dis[nr][nc]==-1){
                            dis[nr][nc] = dis[r][c] + wall;
                            if (wall==0) {
                                q.emplace_front(nr, nc);
                            } else {
                                q.emplace_back(nr, nc);
                            }
                        }
                    }
                }
            }
        }
    }
    cout<<ans<<endl;

    return 0;
}