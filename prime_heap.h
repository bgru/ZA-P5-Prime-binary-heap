#pragma once
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Structure to represent a graph edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a node in the binary heap
struct Node {
    int vertex, key;
};

class MinHeap {
    vector<Node> heap;      // Binary heap
    vector<int> position;   // Position of nodes in the heap
    int size;               // Current size of the heap

    int parent(int i) {
        return (i - 1) / 2;
    }

    int leftChild(int i) {
        return 2 * i + 1;
    }

    int rightChild(int i) {
        return 2 * i + 2;
    }

    void swapNodes(int i, int j) {
        swap(heap[i], heap[j]);
        position[heap[i].vertex] = i;
        position[heap[j].vertex] = j;
    }

    void minHeapify(int i) {
        int left = leftChild(i);
        int right = rightChild(i);
        int smallest = i;

        if (left < size && heap[left].key < heap[smallest].key)
            smallest = left;

        if (right < size && heap[right].key < heap[smallest].key)
            smallest = right;

        if (smallest != i) {
            swapNodes(i, smallest);
            minHeapify(smallest);
        }
    }

public:
    MinHeap(int capacity) {
        heap.resize(capacity);
        position.resize(capacity);
        size = 0;
    }

    void insert(int vertex, int key) {
        if (size == heap.size()) {
            cout << "Heap capacity reached!" << endl;
            return;
        }

        Node newNode;
        newNode.vertex = vertex;
        newNode.key = key;

        int i = size;
        heap[i] = newNode;
        position[vertex] = i;
        size++;

        // Maintain the heap property by performing up-heapify
        while (i > 0 && heap[parent(i)].key > heap[i].key) {
            swapNodes(i, parent(i));
            i = parent(i);
        }
    }

    bool empty() {
        return size == 0;   //Very minimalistic, makes code more readable
    }

    Node extractMin() {
        if (empty()) {
            cout << "Heap is empty!" << endl;
            return { -1, -1 };
        }

        Node minNode = heap[0];
        size--;

        // Replace the root with the last node and perform down-heapify
        heap[0] = heap[size];
        position[minNode.vertex] = 0;
        position[heap[0].vertex] = size;
        minHeapify(0);

        return minNode;
    }

    void decreaseKey(int vertex, int newKey) {
        int i = position[vertex];
        heap[i].key = newKey;

        // Maintain the heap property by performing up-heapify
        while (i > 0 && heap[parent(i)].key > heap[i].key) {
            swapNodes(i, parent(i));
            i = parent(i);
        }
    }


};

class Graph {
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adj; // Adjacency list

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int src, int dest, int weight) {
        adj[src].push_back(make_pair(dest, weight));
        adj[dest].push_back(make_pair(src, weight));
    }

    // Prim's algorithm to find minimum spanning tree
    void primMST() {
        int src = 0; // Start from vertex 0

        // Create a vector for keys and initialize all with infinite (INT_MAX)
        vector<int> key(V, INT_MAX);

        // Create a vector to store the parent of each vertex
        vector<int> parent(V, -1);

        // Create a vector to track if a vertex is included in the MST
        vector<bool> inMST(V, false);

        // Create a binary heap as a priority queue
        MinHeap pq(V);

        // Insert the starting vertex into the priority queue and set its key to 0
        pq.insert(src, 0);
        key[src] = 0;

        while (!pq.empty()) {
            int u = pq.extractMin().vertex;
            inMST[u] = true;

            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // If v is not yet included in the MST and the weight of (u,v) is smaller than the current key of v
                if (!inMST[v] && weight < key[v]) {
                    // Update the key of v and insert it into the priority queue
                    key[v] = weight;
                    pq.decreaseKey(v, key[v]);
                    parent[v] = u;
                }
            }
        }

        // Print the minimum spanning tree
        cout << "Minimum Spanning Tree:" << endl;
        for (int i = 1; i < V; ++i) {
            cout << parent[i] << " - " << i << endl;
        }
    }
};


