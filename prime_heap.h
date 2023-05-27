#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Edge structure
struct Edge {
    int src, dest, weight;
};

// Node structure for heap
struct Node {
    int vertex, key;
};

// Binary heap structure
class BinHeap {
private:
    vector<Node> heap;
    vector<int> pos;

    void swapNode(Node& a, Node& b) {
        Node temp = a;
        a = b;
        b = temp;
    }

    void heapify(int idx) {
        int smallest, left, right;
        smallest = idx;
        left = 2 * idx + 1;
        right = 2 * idx + 2;

        if (left < heap.size() && heap[left].key < heap[smallest].key) {
            smallest = left;
        }
        if (right < heap.size() && heap[right].key < heap[smallest].key) {
            smallest = right;
        }
        if (smallest != idx) {
            pos[heap[idx].vertex] = smallest;
            pos[heap[smallest].vertex] = idx;

            swapNode(heap[idx], heap[smallest]);

            heapify(smallest);
        }
    }

public:
    BinHeap(int size) {
        pos.resize(size);
        for (int i = 0; i < size; ++i) {
            Node node = { i, INT_MAX };
            heap.push_back(node);
            pos[i] = i;
        }
    }

    int getKey(int v) {
        return heap[pos[v]].key;
    }

    void decreaseKey(int v, int key) {
        int i = pos[v];
        heap[i].key = key;

        while (i && heap[i].key < heap[(i - 1) / 2].key) {
            pos[heap[i].vertex] = (i - 1) / 2;
            pos[heap[(i - 1) / 2].vertex] = i;
            swapNode(heap[i], heap[(i - 1) / 2]);

            i = (i - 1) / 2;
        }
    }

    Node extractMin() {
        Node root = heap[0];

        heap[0] = heap[heap.size() - 1];
        pos[heap[0].vertex] = 0;
        pos[root.vertex] = heap.size() - 1;
        heap.pop_back();

        heapify(0);

        return root;
    }

    bool isEmpty() {
        return heap.empty();
    }

    bool isInHeap(int v) {
        return pos[v] < heap.size();
    }
};

// Graph structure
class Graph {
private:
    int V;
    vector<Edge> edges;

public:
    Graph(int V) {
        this->V = V;
    }

    void addEdge(int src, int dest, int weight) {
        edges.push_back({ src, dest, weight });
    }

    void primMST() {
        vector<int> parent(V, -1);
        vector<bool> inMST(V, false); // To check if vertex is included in MST
        BinHeap binHeap(V);

        // Make key value of 0 as 0 and other vertices as infinity
        binHeap.decreaseKey(0, 0);

        // Loop until heap is not empty
        while (!binHeap.isEmpty()) {
            // Extract minimum vertex node
            Node node = binHeap.extractMin();
            int u = node.vertex;

            // Include extracted vertex into MST
            inMST[u] = true;

            // Traverse all edges from extracted vertex and update the keys
            for (Edge edge : edges) {
                int v = (edge.src == u) ? edge.dest : (edge.dest == u) ? edge.src : -1;

                if (v != -1 && inMST[v] == false && edge.weight < binHeap.getKey(v)) {
                    parent[v] = u;
                    binHeap.decreaseKey(v, edge.weight);
                }
            }
        }

        // Print MST
        for (int i = 1; i < V; ++i) {
            cout << parent[i] << " - " << i << endl;
        }
    }

};