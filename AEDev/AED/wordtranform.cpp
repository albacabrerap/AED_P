/*#include <vector>
#include<iostream>
#include <sstream>
#include <unordered_map>
using namespace std;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int n;
    cin>>n;
    vector<unordered_map<string,int>> t(n);
    for (int i = 0; i < n; i++) {
        unordered_map<string, int> v;
        string word;
        while (cin>>word and word!="*") {
            v.emplace(word, word.size());
        }
        t[i]=v;
    }

    vector<pair<string, string>> startendw;

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;

        istringstream ss(line);

        if (string start; ss >> start) {
            if (start.size() < 2) break;

            if (string end; ss >> end) {
                if (end.size()<2 or start.size() != end.size()) break;
                startendw.emplace_back(start,end);
            }
        }
    }


    /*
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

    cout<<cons<<" "<<max<<" "<<isolated;#1#

    return 0;
}*/