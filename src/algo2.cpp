#include <driver.hpp>

void DfsHelper(const std::size_t u, Graph &g, std::vector<bool> &visited,
               std::vector<std::size_t> &degree, const std::size_t k) noexcept {
}

std::vector<std::size_t> KCores(Graph &&g,
                                [[maybe_unused]] const std::size_t k) noexcept {
  std::vector<bool> visited(boost::num_vertices(g), false);
  std::vector<bool> processed(boost::num_vertices(g), false);
  std::vector<std::size_t> degree(boost::num_vertices(g), 0);
  std::size_t start_vertex = 0;
  std::size_t min_degree = std::numeric_limits<std::size_t>::max();
  for (std::size_t i = 0; i < boost::num_vertices(g); ++i) {
    const auto d = boost::degree(i, g);
    if (d < min_degree) {
      min_degree = d;
      start_vertex = i;
    }
    degree[i] = d;
  }

  // perform a DFS from the vertex with the minimum degree
}

int main(const int argc, const char *argv[]) noexcept {
  return Driver(argc, argv);
}