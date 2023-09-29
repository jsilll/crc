#include <driver.hpp>

#include <queue>

std::vector<std::size_t> KCores(Graph &&g, const std::size_t k) noexcept {
  std::queue<std::size_t> q;
  std::vector<std::size_t> degree(boost::num_vertices(g), 0);
  for (std::size_t i = 0; i < boost::num_vertices(g); ++i) {
    const auto d = boost::degree(i, g);
    if (d < k) {
      q.push(i);
    }
    degree[i] = d;
  }
  while (!q.empty()) {
    const auto u = q.front();
    q.pop();
    for (auto it = boost::adjacent_vertices(u, g).first;
         it != boost::adjacent_vertices(u, g).second; ++it) {
      const auto v = *it;
      if (degree[v] >= k) {
        --degree[v];
        if (degree[v] < k) {
          q.push(v);
        }
      }
    }
    boost::clear_vertex(u, g);
  }
  std::vector<std::size_t> core;
  core.reserve(boost::num_vertices(g));
  for (std::size_t i = 0; i < boost::num_vertices(g); ++i) {
    if (boost::degree(i, g) >= k) {
      core.push_back(i);
    }
  }
  return core;
}

int main(const int argc, const char *argv[]) noexcept {
  return Driver(argc, argv);
}