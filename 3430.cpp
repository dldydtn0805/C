// https://www.acmicpc.net/problem/3430

/* 해설

마을에 호수가 여러개 있고, 모두 물이 들어있다

비가 내렸을때 호수가 비어있다면, 호수는 다시 물로 꽉 찬다

만약 호수에 물이 있는데 다시 비가 내릴 경우 호수가 넘쳐흘러 재앙이 온다

용은 비가 오지 않는 날에는 하루에 한개의 호수에 있는 물을 전부 먹는다

비가 오는날에는 물을 마시지 못한다

용이 재앙을 막을 수 있도록 도와주자

---

테스트 케이스의 수 Z가 주어진다

각 테스트 케이스의 첫번째 줄에는 두개의 자연수 N, M이 주어진다

N은 호수의 개수이고, M은 호수에 비가 내리는 날의 수이다

(N, M <= 10^6)

각 테스트 케이스의 둘째 줄에는 t1, t2, t3 ... tm 이 주어진다

만약 ti가 자연수라면, i번째 날에는 ti번 호수에서 비가 내림을 의미한다

ti가 0이라면, i번째 날에는 비가 오지 않음을 의미하고,

이날은 용이 호수로부터 물을 마실 수 있다

용은 비가 오는 날만 물을 마실 수 있다

---

재앙을 막을 수 있다면 YES, 없다면 NO를 출력하라

만약 YES 인 경우, K개의 (자연수, 혹은 0)을 출력하라

K는 일기예보에서 주어진 0의 개수, 즉 비가 오지 않는 날의 수 이다

각 자연수는 용이 물을 마셔야 할 호수의 번호를 나타낸다

만약 0일 경우, 아무 호수에서도 물을 마시지 않음을 의미한다

---

주어지는 정보는 일기예보다.

0이라는 것은 비가 오지 않는다는 것이고, 용이 물을 마실 수 있다는 것을 의미한다

i라는 것은 비가 온다는 것이고, i번 호수에 비가 온다는 것을 의미한다

즉, i가 중복되어 주어진다면, 용이 재앙을 막을 수 없다

반대로 말하면, i와 i 사이에 0이 하나라도 있으면 용은 재앙을 막는다

또한, 호수의 물은 이미 가득 채워져있다.

예컨대,

2 4
0 1 0 2

이라는 것은,

2 4
1 2 0 1 0 2

와 같다는 말이다.

이 경우,

첫번째 0은 1번 호수의 물을 마시고, 두번째 0 은 2번 호수의 물을 마신다

그리고, 1번 호수는 가득 차고, 2번 호수도 가득 차게 된다.



---

따라서 물을 마시는턴을 최대한 유리하게 사용해야한다

트리 세트와 맵을 사용해서 해결할 수 있다

트리 세트에 들어가는 것은 물을 마시는 턴의 인덱스들이다

맵에 들어가는 것은, 각 호수에 이전에 비가 내린 턴의 인덱스들이다.

만약 현재 호수에 비가 내리는 턴이라면,

맵에서 이전에 비가 내린 턴의 인덱스와,

트리 세트에 있는 물을 마시는 턴의 인덱스 들 중,

이전에 내린 턴의 인덱스 보다 높은 값중  가장 작은 값의 것을 소모한다


*/

/* 입력
4
2 4
0 0 1 1
2 4
0 1 0 2
2 3
0 1 2
2 4
0 0 0 1
*/

/* 출력
NO
YES
1 2
NO
YES
0 1 0
*/
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
