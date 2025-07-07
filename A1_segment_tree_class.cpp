/*
    복잡한 경우라면 class가 더 유연하게 handling 할 수 있다.
    직접 짜보니 struct의 tree로도 충분한 것 같기도..
*/

#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void build(vector<int>& data, int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            build(data, 2 * node, start, mid);
            build(data, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l)       // 겹치지 않음
            return 0;
        if (l <= start && end <= r)     // 완전히 포함
            return tree[node];
            
        int mid = (start + end) / 2;
        int left_sum = query(2 * node, start, mid, l, r);
        int right_sum = query(2 * node + 1, mid + 1, end, l, r);
        return left_sum + right_sum;
    }

    void update(int node, int start, int end, int index, int diff) {
        if (index < start || index > end)
            return;
        tree[node] += diff;
        if (start != end) {
            int mid = (start + end) / 2;
            update(2 * node, start, mid, index, diff);
            update(2 * node + 1, mid + 1, end, index, diff);
        }
    }

public:
    SegmentTree(vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 1, 0, n - 1);
    }

    int rangeSum(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void pointUpdate(int index, int newValue, vector<int>& data) {
        int diff = newValue - data[index];
        data[index] = newValue;
        update(1, 0, n - 1, index, diff);
    }
};

int main() {
    vector<int> A = {1, 3, 5, 7, 9, 11};
    SegmentTree st(A);

    cout << st.rangeSum(1, 3) << endl;  // 출력: 15 (3+5+7)
    st.pointUpdate(1, 10, A);           // A[1] = 3 → 10
    cout << st.rangeSum(1, 3) << endl;  // 출력: 22 (10+5+7)

    return 0;
}
