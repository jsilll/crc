#include <driver.hpp>

bool DfsHelper(const std::size_t v, Graph &g, std::vector<bool> &visited,
               std::vector<std::size_t> &degree, const std::size_t k) noexcept {
  visited[v] = true;
  for (auto it = boost::adjacent_vertices(v, g).first;
       it != boost::adjacent_vertices(v, g).second; ++it) {
    const auto u = *it;
    if (degree[v] < k) {
      --degree[u];
    }
    if (!visited[u]) {
      DfsHelper(u, g, visited, degree, k);
    }
  }
  return degree[v] < k;
}

std::vector<std::size_t> KCores(Graph &&g, const std::size_t k) noexcept {
  std::size_t start_vertex = 0;
  std::vector<bool> visited(boost::num_vertices(g), false);
  std::vector<bool> processed(boost::num_vertices(g), false);
  std::vector<std::size_t> degree(boost::num_vertices(g), 0);
  std::size_t min_degree = std::numeric_limits<std::size_t>::max();
  for (std::size_t i = 0; i < boost::num_vertices(g); ++i) {
    const auto d = boost::degree(i, g);
    if (d < min_degree) {
      min_degree = d;
      start_vertex = i;
    }
    degree[i] = d;
  }
  DfsHelper(start_vertex, g, visited, degree, k);
  for (std::size_t i = 0; i < boost::num_vertices(g); ++i) {
    if (!visited[i]) {
      DfsHelper(i, g, visited, degree, k);
    }
  }
  for (std::size_t i = 0; i < boost::num_vertices(g); ++i) {
    if (degree[i] >= k) {
      std::uint32_t count = 0;
      for (auto it = boost::adjacent_vertices(i, g).first;
           it != boost::adjacent_vertices(i, g).second; ++it) {
        const auto u = *it;
        if (degree[u] >= k) {
          ++count;
        }
      }
      if (count < k) {
        processed[i] = true;
      }
    }
  }
  std::vector<std::size_t> core;
  core.reserve(boost::num_vertices(g));
  for (std::size_t i = 0; i < boost::num_vertices(g); ++i) {
    if (degree[i] >= k) {
      core.push_back(i);
    }
  }
  return core;
}

int main(const int argc, const char *argv[]) noexcept {
  return Driver(argc, argv);
}