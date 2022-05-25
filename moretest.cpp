#include<iostream>
#include<list>
#include<vector>

using namespace std;

/*
         1
        /|\
       / | \
     9/  |7 \3
     / 3 |   \
    0----4----2
     \   | 1 /
     2\  |1 /-2
       \ | /
        \|/
         3
*/

class Edge {

    public:
        int src;
        int dst;
        int weight;
        Edge () {}
        Edge (int src, int dst, int weight) {
            this->src = src;
            this->dst = dst;
            this->weight = weight;
        }
};

class Graph {

    private:
        vector<Edge> edge_list;
        int nodes;
        // distance is a 2-dimensional array that stores the shortest distance between [src][dst]
        vector<vector<int>> distance;
        // next is a 2-dimensional array that stores the node next to the source. This is used
        // for path construction between [src][dst]
        vector<vector<int>> next;

    public:

        Graph() {}

        Graph (int n) {
            nodes = n;
            distance.resize(n);
            next.resize(n);

            for (int i=0; i<n; i++) {
                distance[i].resize(n, 999999999); // 999999999 indicates infinite distance
                next[i].resize(n, -1);
            }
        }

        void AddEdge (int src, int dst, int weight, bool isbidirectional) {
            Edge e(src, dst, weight);
            edge_list.push_back(e);
            if (isbidirectional) {
                Edge e(dst, src, weight);
                edge_list.push_back(e);
            }
        }

        void Floyd_Warshall() {

            for (int i=0; i<nodes; i++) {
                distance[i][i] = 0;
                next[i][i] = i;
            }

            for (auto edge : edge_list) {
                int u = edge.src;
                int v = edge.dst;
                distance[u][v] = edge.weight;
                next[u][v] = v;
            }

            for (int k=0; k<nodes; k++) {
                for (int i=0; i<nodes; i++) {
                    for (int j=0; j<nodes; j++) {
                        if (distance[i][j] > distance[i][k] + distance[k][j]) {
                            distance[i][j] = distance[i][k] + distance[k][j];
                            next[i][j] = next[i][k];
                        }
                    }
                }
            }

            cout << "Shortest distance between nodes" << endl;
            for (int u=0; u<nodes; u++) {
                for (int v=u+1; v<nodes; v++) {
                    cout << "\nDistance ( " << u << " - " << v << " ) : " << distance[u][v] << endl;
                    PathConstruction(u, v);
                }
            }
        }

        // Construct path from source node to destination node
        void PathConstruction (int src, int dst) {

            cout << "# Path between " << src << " and " << dst << " : ";

            if (next[src][dst] == -1) {
               cout << "No path exists" << endl;
            } else {
               vector<int> path;
               path.push_back(src);

               while (src != dst) {
                   src = next[src][dst];
                   path.push_back(src);
               }

               for (auto& it : path)
                   cout << it << " ";
               cout << endl;
            }
        }
};

int main() {

    Graph g(5);

    // Edges from node 0
    // AddEdge(src, dst, weight, bi-directional(true/false))
    g.AddEdge(0, 1, 9, true);
    g.AddEdge(0, 3, 2, true);
    g.AddEdge(0, 4, 3, true);

    // Edges from node 1
    g.AddEdge(1, 2, 3, true);
    g.AddEdge(1, 4, 7, true);

    // Edges from node 2
    // Edge from 2 -> 3 is unidirectional. If it was bidirectional, it would introduce negative weight cycle
    // causing the Floyd-Warshall algorithm to fail.
    g.AddEdge(2, 3, -2, false);
    g.AddEdge(2, 4, 1, true);

    // Edges from node 3
    g.AddEdge(3, 4, 1, true);

    g.Floyd_Warshall();

    return 0;
}
