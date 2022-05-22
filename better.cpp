#include <algorithm>
#include <sstream>
#include <fstream>
#include<iostream>
#include<list>
#include<vector>
#include<queue>

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
int yourchoice,temp=0, srcIndex, dstIndex;
queue<int> Xqueue,Yqueue;
string source, destination;
struct Node{
        string Name;
        int Xpos;
        int Ypos;
        Node () {}
        Node(string Name, int Xpos, int Ypos) {
            this->Name = Name;
            this->Xpos = Xpos;
            this->Ypos = Ypos;
        }
};
struct Edge {

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
        list<Edge> edge_list;
        vector<Node> nodeVector;
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
            Node test1("St", 1, 8);
            Node test2("Swet", 4, 2);
            nodeVector.push_back(test1);
            nodeVector.push_back(test2);
            distance.resize(n);
            next.resize(n);

            for (int i=0; i<n; i++) {
                distance[i].resize(n, 999999999); // 999999999 indicates infinite distance
                next[i].resize(n, -1);
            }
        }

        void AddEdge (int src, int dst, int weight) {
            Edge forward(src, dst, weight);
            edge_list.push_back(forward);
            Edge backward(dst, src, weight);
            edge_list.push_back(backward);

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
        }

        // Construct path from source node to destination node
        void PathConstruction (int src, int dst) {

            cout << "# Path between " << src << " and " << dst << " : ";

            if (next[src][dst] == -1) {
               cout << "No path exists" << endl;
            }
            else {
                vector<int> path;
                path.push_back(src);

                while (src != dst) {
                    src = next[src][dst];
                    path.push_back(src);
                }

                cout << "START\n";
                for (auto& it : path)
                    cout << it << " ";
                 cout << "END" << endl;

                for(auto& it : path){
                    Xqueue.push(nodeVector[it-1].Xpos);
                    Yqueue.push(nodeVector[it-1].Ypos);
                }

                for(int i = 0; i < nodeVector.size(); i++){
                    if(nodeVector[i].Name == source){
                        srcIndex = i+1;
                    }
                    if(nodeVector[i].Name == destination){
                        dstIndex = i+1;
                    }
                }
                cout << " srcIndex = " << srcIndex << "dstIndex = " << dstIndex;
        }

    }
};

void ReadFile(vector<Node> nodeVector, string fileName){
    fstream newfile;
    int X,Y;
    newfile.open(fileName,ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){ //checking whether the file is open
      string tp;
      while(getline(newfile, tp)){ //read data from file object and put it into string.
    stringstream objX, objY;
          string name = tp.substr(0,tp.find(":"));
          string Xtemp = tp.substr(tp.find(":")+1,1);
          objX << Xtemp;
          objX >> X;
          string Ytemp = tp.substr(tp.find(";")+1,1);
          objY << Ytemp;
          objY >> Y;
          Node entry(name,X,Y);
          nodeVector.push_back(entry);

        }
      newfile.close(); //close the file object.
   }
   /*for(int i = 0; i < nodeVector.size(); i++){
       cout << nodeVector[i].Name << endl;
       cout << nodeVector[i].Xpos << endl;
       cout << nodeVector[i].Ypos << endl;
    }*/
}

void Start() {
    system("clear");
    cout<<"===================================================== \n";
    cout<<" \t\t START \t \n";
    cout<<"===================================================== \n";
    cout<< "Please enter your current position: ";
    cin >> source;
    cout<< "Please enter your destination: ";
    cin >> destination;
}

void displaymenu() {
    string confirm;
    do {
        system("clear");
        cout<<"===================================================== \n";
        cout<<" \t\tMENU \t \n";
        cout<<"===================================================== \n";
        cout<<" 1.Start\n";
        cout<<" 2.Exit\n";
        cout<<"Enter your choice(1-5):";
        cin>>yourchoice;
        switch (yourchoice)
        {
            case 1: Start(); break;
            case 2: break;
            default: cout<<"invalid"; break;
        }
    } while (yourchoice !=2 );
    system("clear");
}

int main() {

    displaymenu();

    Graph g(5);

    // Edges from node 0
    // AddEdge(src, dst, weight, bi-directional(true/false))
    g.AddEdge(0, 1, 9);
    g.AddEdge(0, 3, 2);
    g.AddEdge(0, 4, 3);

    // Edges from node 1
    g.AddEdge(1, 2, 3);
    g.AddEdge(1, 4, 7);

    // Edges from node 2
    // Edge from 2 -> 3 is unidirectional. If it was bidirectional, it would introduce negative weight cycle
    // causing the Floyd-Warshall algorithm to fail.
    g.AddEdge(2, 3, -2);
    g.AddEdge(2, 4, 1);

    // Edges from node 3
    g.AddEdge(3, 4, 1);

    g.Floyd_Warshall();
    cout << "\n";
    g.PathConstruction(1, 2);

    return 0;
}
