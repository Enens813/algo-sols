#include <iostream>
#include <queue>

int am[1001][1001];
int visited[1001];

int n; int m; int v;

void dfs(int v){
    visited[v] = 1;
    std::cout << v << " "; 
    for (int i=1; i<=n; i++){
        if (am[v][i] == 1 && visited[i] == 0) dfs(i);
    }
}

std::queue<int> q;

void visit(int v){
    q.push(v);
    visited[v]=1;
    std::cout << v << " ";
}

void bfs(int v){
    visit(v);
    while (!q.empty()){
        int w = q.front();
        q.pop();
        for (int i=1; i<=n; i++){
            if (am[w][i] == 1 && visited[i] == 0) visit(i);
        }
    }
}

int main(){
    std::cin >> n;
    std::cin >> m;
    std::cin >> v;
    
    for (int i=1; i<1001; i++){
        visited[i]=0;
        for (int j=1; j<1001; j++){
            am[i][j]=0;
        }
    }
    for (int i=1; i<=m; i++){
        int j; int k;
        std::cin >> j;
        std::cin >> k;
        am[j][k] = 1;
        am[k][j] = 1;
    }

    dfs(v);
    for (int i=1; i<1001; i++) visited[i]=0;
    std::cout << std::endl;
    bfs(v);

    return 0;
}