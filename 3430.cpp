#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <sstream>

using namespace std;

string greedy(const vector<int>& weatherCast, int N, int M) {
    set<int> ts; // TreeSet -> set
    unordered_map<int, int> hm; // HashMap -> unordered_map
    for (int i = 1; i <= N; ++i) {
        hm[i] = -1;
    }
    vector<int> ans(M, 0);
    for (int i = 0; i < M; ++i) {
        if (weatherCast[i] == 0) {
            ts.insert(i);
        } else {
            auto it = ts.upper_bound(hm[weatherCast[i]]);
            if (it != ts.end()) {
                int drinkTurn = *it;
                ans[drinkTurn] = weatherCast[i];
                ts.erase(it);
                hm[weatherCast[i]] = i;
            } else {
                return "NO\n";
            }
        }
    }
    stringstream ss;
    ss << "YES\n";
    for (int i = 0; i < M; ++i) {
        if (weatherCast[i] == 0) {
            ss << ans[i] << " ";
        }
    }
    ss << "\n";
    return ss.str();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Z;
    cin >> Z;
    string output;
    while (Z--) {
        int N, M;
        cin >> N >> M;
        vector<int> weatherCast(M);
        for (int i = 0; i < M; ++i) {
            cin >> weatherCast[i];
        }
        output += greedy(weatherCast, N, M);
    }
    cout << output;
    return 0;
}
