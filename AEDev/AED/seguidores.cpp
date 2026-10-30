/*#include <vector>
#include<iostream>
using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> li(n+1, {0, 0});
    vector<vector<int>> ad(n+1);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        ad[x].push_back(y);
        ad[y].push_back(x);
        li[x].second++;
    }
    for (int i = 1; i < n; i++) {


    }
    
    return 0;
}*/