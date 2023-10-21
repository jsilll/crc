#pragma once

#include <graph.hpp>

#include <iostream>
#include <queue>

std::vector<std::size_t> Algo1(Graph &&g, const std::size_t k) noexcept {
  std::queue<std::size_t> q;
  std::vector<std::size_t> degree(boost::num_vertices(g), 0);
  for (std::size_t i = 0; i < boost::num_vertices(g); ++i) {
    const auto d = boost::degree(i, g);
    if (d < k) {
#ifdef DEBUG
      std::cout << "push " << i << "\n";
#endif
      q.push(i);
    }
#ifdef DEBUG
    std::cout << "degree " << i << " " << d << "\n";
#endif
    degree[i] = d;
  }
  while (!q.empty()) {
    const auto u = q.front();
    q.pop();
#ifdef DEBUG
    std::cout << "pop " << u << "\n";
#endif
    for (auto it = boost::adjacent_vertices(u, g).first;
         it != boost::adjacent_vertices(u, g).second; ++it) {
      const auto v = *it;
#ifdef DEBUG
      std::cout << "visit " << v << "\n";
#endif
      if (degree[v] >= k) {
#ifdef DEBUG
        std::cout << "decrement " << v << "\n";
#endif
        --degree[v];
        if (degree[v] < k) {
#ifdef DEBUG
          std::cout << "push " << v << "\n";
#endif
          q.push(v);
        }
      }
    }
#ifdef DEBUG
    std::cout << "clear " << u << "\n";
#endif
    boost::clear_vertex(u, g);
  }
  std::vector<std::size_t> cores;
  cores.reserve(boost::num_vertices(g));
  for (std::size_t i = 0; i < boost::num_vertices(g); ++i) {
    if (boost::degree(i, g) >= k) {
      cores.push_back(i);
    }
  }
  return cores;
}