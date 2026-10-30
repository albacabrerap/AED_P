/*#include <vector>
#include <iostream>
using namespace std;
int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int n, m;
    cin>>n>>m;
    vector<string> v(n);
    for(int i=0;i<n;i++) {
        cin>>v[i];
    }
    vector<int> cont(5,0);
    int P=0;

    int df[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (v[i][j] == '#') {
                int deg=0;
                for (int k = 0; k < 4; k++) {
                    int f_n = i + df[k];
                    int g_n = j + dc[k];
                    if (f_n >= 0 and f_n < n and g_n >= 0 and g_n < m and v[f_n][g_n] == '#') {
                        deg++;
                    }
                }
                cont[deg]++;
                P+=4-deg;
            }
        }

    }

    cout<<P<<" ";
    for (int i = 0; i < 5; i++) {
        cout<<cont[i]<<" ";
    }

    return 0;
}*/