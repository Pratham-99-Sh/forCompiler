#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 1e9 + 7;
vector<int> gr[100001];
long long dp[100001];

long long dfs(int u, int dest) {
    if (u == dest) {
        return 1;
    }
    if (dp[u] != -1) {
        return dp[u];
    }
    long long c = 0;
    for (int v : gr[u]) {
        c = (c + dfs(v, dest)) % MOD;
    }
    dp[u] = c;
    return c;
}

int main() {
    int n, m, source, dest;
    cout << "Enter the number of intersections : ";
    cin >> n;
    cout << "Enter the number of roads : ";
    cin >> m;
    cout << "Enter Source (Chef's current Location) : ";
    cin >> source;
    cout << "Enter Destination (Townhall) : ";
    cin >> dest;
    
    cout << "Enter the pair of Intersections which have road connecting them :\n";

    memset(dp, -1, sizeof(dp));

    for (int i = 0; i <= n; ++i) {
        gr[i].clear();
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        gr[u].push_back(v);
    }

    long long ans = dfs(source, dest);
    cout << "Number of ways to reach Townhall : " << ans % MOD << "\n" << endl;

    return 0;
}