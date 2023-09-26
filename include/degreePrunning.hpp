#pragma once
#include <utils.hpp>

void degreePruning(Graph g,int k) {
        

        // Initialize degrees
        for (int i = 0; i < V; ++i) {


            degree[i] = g[i].size();
            if (degree[i] < k) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // Remove vertex u and update degrees of its neighbors
            for (int v : adj[u]) {
                if (degree[v] >= k) {
                    degree[v]--;
                    if (degree[v] < k) {
                        q.push(v);
                    }
                }
            }

            // Remove u from the graph
            adj[u].clear();
        }
}