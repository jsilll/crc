#include <utils.hpp>

#include <iostream>
#include <queue>

void degreePruning(Graph g,int k) {
        
        // initialize the degree vector with the size of the graph
        std::vector<int> degree(boost::num_vertices(g));
        // initialize the queue
        std::queue<int> q;

        // iterate over the vertices and initialize the degree vector
        for (int i = 0; i < boost::num_vertices(g); ++i) {
            int d = boost::degree(i, g);
            degree[i] =d;
            if (degree[i] < k) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // Remove vertex u and update degrees of its neighbors
            for(auto it = boost::adjacent_vertices(u, g).first; 
            it != boost::adjacent_vertices(u, g).second; ++it) {
                int v = *it;
                if (degree[v] >= k) {
                    degree[v]--;
                    if (degree[v] < k) {
                        q.push(v);
                    }
                }
            }

            // Remove u from the graph
            boost::clear_vertex(u, g);
        }
}

int main(const int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <graph file>" << std::endl;
        return EXIT_FAILURE;
    }

    Graph g;

    try
    {
        g = ReadGraphMtx(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    std::cout << "Number of vertices: " << boost::num_vertices(g) << std::endl;
    std::cout << "Number of edges: " << boost::num_edges(g) << std::endl;

    return EXIT_SUCCESS;
}