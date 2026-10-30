/*#include <vector>
#include<iostream>
using namespace std;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int n, l;
    cin>>n>>l;

    vector<string> v(n);
    for(int i=0;i<n;i++) {
        cin>>v[i];
    }

    vector<int> deg(n+1,0);
    int cons=0;

    for (int i=0;i<n;i++) {
        for (int j=i+1;j<n;j++) {
            int dif=0;
            for (int k=0;k<l;k++) {
                if (v[i][k]!=v[j][k]) {
                    dif++;
                }
            }
            if (dif==1) {
                cons++;
                deg[i]++;
                deg[j]++;
            }
        }
    }

    int max=0;
    int isolated=0;
    for (int i=0;i<n;i++) {
        if (deg[i]>max) {
            max=deg[i];
        }
        if (deg[i]==0) {
            isolated++;
        }
    }

    cout<<cons<<" "<<max<<" "<<isolated;
    return 0;
}*/