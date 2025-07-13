/*
    아이디어: UnionFind 이용, 숫자가 같으면서 겹치는 것들 찾기

    시행착오: tree구조로 생성 가능할 것 같았는데...
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;       // 세금 누적합의 최댓값은 값의 최대(10^9) * 개수최대 (1000*1000) = 10^15. 그러나 int범위는 2*10^9 (4byte). long long은 9*10^18까지 가능(8byte).

// Disjoint Set Union(Union find) 알고리즘 구현체
struct DSU {
    vector<int> parent, rnk;    // 각 node의 parent 와 rank를 저장
    vector<ll> compSum;         // 각 node가 가장 높은 height일 때의 tax 합을 저장

    // 생성자
    DSU(int n, const vector<ll>& c): parent(n), rnk(n,0), compSum(c) {
        iota(parent.begin(), parent.end(), 0);
    }

    // Union find 알고리즘의 find 함수
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    // Union find 알고리즘의 union 함수
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;

        // union by rank
        if (rnk[a] < rnk[b]) swap(a,b);     // 항상 b가 a밑으로 들어가게 변수 조정
        parent[b] = a;

        if (rnk[a] == rnk[b]) rnk[a]++;

        // b가 a밑으로 들어가고, a에 b 밑의 tax를 더함. (일종의 dp)
        compSum[a] += compSum[b];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    int NM = N * M;

    // 1) 입력
    vector<int> h(NM);
    for(int i = 0; i < NM; i++) {
        cin >> h[i];
    }
    vector<ll> c(NM);
    for(int i = 0; i < NM; i++) {
        cin >> c[i];
    }

    // 2) 높이 + 인덱스 정렬
    vector<pair<int,int>> cells(NM);
    for(int i = 0; i < NM; i++) {
        cells[i] = {h[i], i};
    }
    // sort 함수로 정렬(begin에서 end까지 lambda를 기준으로.), lambda 함수로 정렬 기준 정의 (first(height) 비교, 높이가 낮은 순서대로 정렬(오름차순))
    sort(cells.begin(), cells.end(),
         [](auto &a, auto &b){ return a.first < b.first; });

    // 3) DSU 초기화, 활성화 표시, 정답 저장소
    DSU dsu(NM, c);
    vector<bool> active(NM, false);
    vector<ll> ans(NM, 0);

    // 4) 같은 높이 그룹별로 활성화 → union → 결과 기록
    int idx = 0;
    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};

    while(idx < NM) {
        int currH = cells[idx].first;

        int start = idx;
        // 같은 높이 그룹의 범위 찾기
        while(idx < NM && cells[idx].first == currH) {
            idx++;
        }
        int end = idx;

        // (1) 그룹 내 모든 칸 활성화 & 이웃과 합집합
        for(int t = start; t < end; t++) {
            int id = cells[t].second;
            active[id] = true;      // 자기자신 활성화
            int x = id / M;         // 좌표 복원
            int y = id % M;

            for(int d = 0; d < 4; d++) {
                // 이웃 좌표가 범위 안에 들어오는지 확인
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;

                // 활성화가 되어있다면 자신을 기준으로 합친다. (이미 활성화가 되어있다 = 자신보다 작거나 같다. = 자신이 '성'일 때)
                int nid = nx * M + ny;
                if (active[nid]) {      
                    dsu.unite(id, nid);
                }
            }
        }
        // (2) 그룹 내 각 칸의 정답 기록
        // "같은 높이 그룹의 범위"에서 root를 찾음. 즉, 이건 같은 height이 이어져있는 경우의 root를 찾아주는 것.
        for(int t = start; t < end; t++) {
            int id = cells[t].second;
            int root = dsu.find(id);        // 자신이 속한 component의 root을 찾음.
            ans[id] = dsu.compSum[root];
        }
    }

    // 5) 출력
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cout << ans[i * M + j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
