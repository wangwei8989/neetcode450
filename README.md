# neetcode450
all of the problems i solved on leetcode

## table of the context
    two points
    sliding window
    stack
    binary search
    linked list
    bit manipulation
    graph

## bit manipulation
    x & -x : Find the rightmost set bit
    n & (n-1): clears the lowest set bit in the binary representation of n.

    Original code, complement code, inverse code

## graph
### MST
    A Minimum Spanning Tree (MST) is a subset of the edges of a connected, undirected graph that connects all the vertices together without any cycles and with the minimum possible total edge weight. 
    Here's how you can formally define a Minimum Spanning Tree:
        Given a connected, undirected graph \( G = (V, E) \) with \( V \) vertices and \( E \) edges, a Minimum Spanning Tree \( T \) of \( G \) is a spanning tree of \( G \) (i.e., a subgraph that is a tree and connects all the vertices) such that:
        1. \( T \) contains all the vertices of \( G \).
        2. The total weight of the edges in \( T \) is minimized.

    Properties of MST:
    1. Unique: A graph can have multiple spanning trees, but if the edge weights are distinct, then the MST is unique.
    2. V - 1 Edges: An MST of a graph with \( V \) vertices has exactly \( V - 1 \) edges.
    3. Acyclic: An MST does not contain any cycles.
    4. Connectivity: An MST ensures that all vertices are connected.

    Algorithms for Finding MST:
        Kruskal's Algorithm
        Prim's Algorithm

    Example:
        Consider the following graph:
        ```
             2
          1 ---- 2
          |\   /|
          | \ / |
         3|  X  |1
          | / \ |
          |/   \|
          3 ---- 4
             4
        ```
        For this graph, one of the Minimum Spanning Trees would be:
        ```
             2
          1 ---- 2
          |      |
          |      |
         3|      |1
          |      |
          |      |
          3 ---- 4
             4
        ```
    Summary
        A Minimum Spanning Tree is a fundamental concept in graph theory and has various applications in network design, clustering, and optimization problems. It is defined as a subgraph of the original graph that is a tree, connects all the vertices, and has the minimum possible total edge weight. Algorithms like Kruskal's and Prim's are commonly used to find the MST efficiently.

### DSU
### Dijstra's algorithm
### Prim's algorithm
    