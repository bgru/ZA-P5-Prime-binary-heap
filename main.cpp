#include "prime_heap.h"

int main() {

    int V = 7; // Number of vertices
    Graph g(V);

    // Adding edges to the graph
    g.addEdge(0, 1, 11);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 3);
    g.addEdge(5, 6, 4);
    g.addEdge(6, 0, 12);
    g.addEdge(4, 0, 15);
    g.addEdge(4, 1, 9);
    g.addEdge(4, 2, 8);
    g.addEdge(4, 3, 3);
    g.addEdge(4, 5, 3);
    g.addEdge(4, 6, 5);


    // Find the minimum spanning tree using Prim's algorithm
    g.primMST();

    return 0;
}