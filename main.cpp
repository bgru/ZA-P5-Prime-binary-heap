#include "prime_heap.h"

int main() {
    int V = 6; // Number of vertices

    Graph g(V);

    // Adding edges to the graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);

    // Find the minimum spanning tree using Prim's algorithm
    g.primMST();

    return 0;
}