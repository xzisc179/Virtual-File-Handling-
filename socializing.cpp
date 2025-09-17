#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// BFS to count reachable nodes within N degrees
int bfs(const vector<vector<int>>& graph, int start, int maxDepth) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<pair<int, int>> q; // {node, current_depth}
    visited[start] = true;
    q.push({start, 0});
    int count = 0; // exclude start or include as you like

    while (!q.empty()) {
        auto [node, depth] = q.front(); q.pop();
        if (depth > 0) count++;  // count reachable excluding start node
        if (depth == maxDepth) continue;

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push({neighbor, depth + 1});
            }
        }
    }
    return count;
}

// DFS helper function to count reachable nodes within N degrees
void dfsHelper(const vector<vector<int>>& graph, int node, int depth, int maxDepth, vector<bool>& visited, int& count) {
    if (depth > maxDepth) return;
    if (depth > 0) count++;
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfsHelper(graph, neighbor, depth + 1, maxDepth, visited, count);
        }
    }
}

// DFS wrapper
int dfs(const vector<vector<int>>& graph, int start, int maxDepth) {
    int n = graph.size();
    vector<bool> visited(n, false);
    int count = 0;
    dfsHelper(graph, start, 0, maxDepth, visited, count);
    return count;
}

int main() {
    int n, m, maxDepth;
    cout << "Enter number of people and friendships: ";
    cin >> n >> m;
    vector<vector<int>> graph(n);

    cout << "Enter friendship pairs (u v):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << "Enter max degrees of separation: ";
    cin >> maxDepth;

    // Store reach counts for BFS and DFS
    vector<int> bfsReach(n), dfsReach(n);

    for (int person = 0; person < n; person++) {
        bfsReach[person] = bfs(graph, person, maxDepth);
        dfsReach[person] = dfs(graph, person, maxDepth);
    }

    int maxBFS = *max_element(bfsReach.begin(), bfsReach.end());
    int maxDFS = *max_element(dfsReach.begin(), dfsReach.end());

    cout << "\nSocial Network Influencer(s) by BFS (max reach = " << maxBFS << "): ";
    for (int i = 0; i < n; i++) {
        if (bfsReach[i] == maxBFS)
            cout << i << " ";
    }

    cout << "\nSocial Network Influencer(s) by DFS (max reach = " << maxDFS << "): ";
    for (int i = 0; i < n; i++) {
        if (dfsReach[i] == maxDFS)
            cout << i << " ";
    }

    cout << endl;
    return 0;
}
