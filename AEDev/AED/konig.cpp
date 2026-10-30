/*#include <vector>
#include<iostream>
using namespace std;

string konig(int n, int m) {

    vector<vector<int>> g(n+1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int odd=0;
    for (int i = 1; i < n; i++) {
        if (g[i].size()%2!=0) {
            odd++;
        }
        if (odd>2) {
            return "IMPOSIBLE";
        }

    }

    if (odd==0) {
        return "CIRCUITO";
    }
    return "CAMINO";


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    if (m<n-1) {
        cout<<"IMPOSIBLE";
    } else {
        cout<<konig(n, m);
    }

    return 0;
}*/