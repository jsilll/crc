#pragma once

#include <graph.hpp>

#include <iostream>
#include <stack>

void DfsHelper(const std::size_t u, const Graph &g, std::vector<bool> &visited,
               std::vector<std::size_t> &degree, const std::size_t k) noexcept {
  std::stack<std::size_t> st;
#ifdef DEBUG
  std::cout << "push " << u << "\n";
  std::cout << "visited " << u << "\n";
#endif
  st.push(u);
  visited[u] = true;
  while (!st.empty()) {
    const auto v = st.top();
#ifdef DEBUG
    std::cout << "pop " << v << "\n";
#endif
    st.pop();
    if (degree[v] < k) {
      for (auto it = boost::adjacent_vertices(v, g).first;
           it != boost::adjacent_vertices(v, g).second; ++it) {
        const auto w = *it;
#ifdef DEBUG
        std::cout << "decrement " << w << "\n";
#endif
        --degree[w];
        if (!visited[w]) {
#ifdef DEBUG
          std::cout << "push " << w << "\n";
          std::cout << "visited " << w << "\n";
#endif
          st.push(w);
          visited[w] = true;
        }
      }
    } else {
      for (auto it = boost::adjacent_vertices(v, g).first;
           it != boost::adjacent_vertices(v, g).second; ++it) {
        const auto w = *it;
        if (!visited[w]) {
#ifdef DEBUG
          std::cout << "push " << w << "\n";
          std::cout << "visited " << w << "\n";
#endif
          st.push(w);
          visited[w] = true;
        }
      }
    }
  }
}

std::vector<std::size_t> Algo2(Graph &&g, const std::size_t k) noexcept {
  std::vector<bool> visited(boost::num_vertices(g), false);
  std::vector<std::size_t> degree(boost::num_vertices(g), 0);

  std::size_t start_vertex = 0;
  std::size_t min_degree = std::numeric_limits<std::size_t>::max();
  for (std::size_t i = 0; i < boost::num_vertices(g); ++i) {
    const auto d = boost::degree(i, g);
    if (d < min_degree) {
      min_degree = d;
      start_vertex = i;
    }
#ifdef DEBUG
    std::cout << "degree " << i << " " << d << "\n";
#endif
    degree[i] = d;
  }
#ifdef DEBUG
  std::cout << "start vertex " << start_vertex << "\n";
#endif
  DfsHelper(start_vertex, g, visited, degree, k);
#ifdef DEBUG
  std::cout << "check visited\n";
#endif
  for (std::size_t i = 0; i < boost::num_vertices(g); ++i) {
    if (!visited[i]) {
#ifdef DEBUG
      std::cout << "dfs " << i << "\n";
#endif
      DfsHelper(i, g, visited, degree, k);
    }
  }
  for (std::size_t i = 0; i < boost::num_vertices(g); ++i) {
    if (degree[i] >= k) {
#ifdef DEBUG
      std::cout << "degree " << i << " " << degree[i] << "\n";
#endif
      std::uint32_t count = 0;
      for (auto it = boost::adjacent_vertices(i, g).first;
           it != boost::adjacent_vertices(i, g).second; ++it) {
        const auto u = *it;
        if (degree[u] >= k) {
          ++count;
        }
      }
#ifdef DEBUG
      std::cout << "count " << i << " " << count << "\n";
#endif
      degree[i] = count;
    }
  }
  std::vector<std::size_t> cores;
  cores.reserve(boost::num_vertices(g));
  for (std::size_t i = 0; i < boost::num_vertices(g); ++i) {
    if (degree[i] >= k) {
      cores.push_back(i);
    }
  }
  return cores;
}