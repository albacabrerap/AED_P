/*#include <iostream>
#include <vector>

using namespace std;


int recmud(vector<int>& weights, int& n, int idx, int sum0, int sum1, int sum2) {
    if (idx == n) {
        return max(sum0, max(sum1, sum2));
    }
    int op0 = recmud(weights,n, idx + 1, sum0 + weights[idx], sum1, sum2);
    int op1 = recmud(weights,n, idx + 1, sum0, sum1 + weights[idx], sum2);
    int op2 = recmud(weights,n, idx + 1, sum0, sum1, sum2 + weights[idx]);

    return min(op0, min(op1, op2));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    cout << recmud(weights,n,0, 0, 0, 0);

    return 0;
}*/