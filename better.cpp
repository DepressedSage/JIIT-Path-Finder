#include <algorithm>
#include <sstream>
#include <fstream>
#include<iostream>
#include<list>
#include <string>
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
        string Building;
        string Floor;
        int Xpos;
        int Ypos;
        Node () {}
        Node(string Name,string Building,string Floor, int Xpos, int Ypos) {
            this->Name = Name;
            this->Building = Building;
            this->Floor = Floor;
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

list<Edge> edgeList;
vector<Node> nodeVector;

class Graph {

    private:
        int nodes;
        // distance is a 2-dimensional array that stores the shortest distance between [src][dst]
        vector<vector<int>> distance;
        // next is a 2-dimensional array that stores the node next to the source. This is used
        // for path construction between [src][dst]
        vector<vector<int>> next;

    public:

        Graph() {}

        void ReadEdgesFile(list<Edge> edgeList){
            fstream newfile;
            int src,dst,weight;
            newfile.open("Nodes.txt",ios::in); //open a file to perform read operation using file object
            if (newfile.is_open()){ //checking whether the file is open
              string tp;
              while(getline(newfile, tp)){ //read data from file object and put it into string.
            stringstream objS,objD,objW;
                  string tempsrc = tp.substr(0,tp.find(":"));
                  objS << tempsrc;
                  objS >> src;
                  string tempdst = tp.substr(tp.find(":")+1,tp.find(";"));
                  objD << tempdst;
                  objD >> dst;
                  string tempW = tp.substr(tp.find(";")+1,1);
                  objW << tempW;
                  objW >> weight;
                    Edge forward(src, dst, weight);
                    edgeList.push_back(forward);
                    Edge backward(dst, src, weight);
                    edgeList.push_back(backward);
                }
              newfile.close(); //close the file object.
           }
           /*for(int i = 0; i < nodeVector.size(); i++){
               cout << nodeVector[i].Name << endl;
               cout << nodeVector[i].Xpos << endl;
               cout << nodeVector[i].Ypos << endl;
            }*/
        }
        void ReadNodeFile(vector<Node> nodeVector){
            fstream newfile;
            int X,Y;
            newfile.open("Edges.txt",ios::in); //open a file to perform read operation using file object
            if (newfile.is_open()){ //checking whether the file is open
              string tp;
              while(getline(newfile, tp)){ //read data from file object and put it into string.
            stringstream objX, objY;
                  string name = tp.substr(0,tp.find("."));
                  string building = tp.substr(tp.find(".")+1,tp.find(","));
                  string floor = tp.substr(tp.find(",")+1,tp.find(":"));
                  string Xtemp = tp.substr(tp.find(":")+1,1);
                  objX << Xtemp;
                  objX >> X;
                  string Ytemp = tp.substr(tp.find(";")+1,1);
                  objY << Ytemp;
                  objY >> Y;
                  Node entry(name,building,floor,X,Y);
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

        Graph (int n) {
            nodes = n;
            distance.resize(n);
            next.resize(n);
            ReadNodeFile(nodeVector);
            ReadEdgesFile(edgeList);

            for (int i=0; i<n; i++) {
                distance[i].resize(n, 999999999); // 999999999 indicates infinite distance
                next[i].resize(n, -1);
            }
        }


        void Floyd_Warshall() {

            for (int i=0; i<nodes; i++) {
                distance[i][i] = 0;
                next[i][i] = i;
            }

            for (auto edge : edgeList) {
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

            }

        }


};


void Start() {
    system("clear");
    cout<<"===================================================== \n";
    cout<<" \t\t START \t \n";
    cout<<"===================================================== \n";
    cout<< "Please enter your current position: ";
    cin >> source;
    cout<< "Please enter your destination: ";
    cin >> destination;
    for(int i = 0; i < nodeVector.size(); i++){
        if(nodeVector[i].Name == source){
            srcIndex = i+1;
        }
        if(nodeVector[i].Name == destination){
            dstIndex = i+1;
        }
    }

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
        cout<<"Enter your choice(1-2):";
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

    Graph g(5);
    g.Floyd_Warshall();
    displaymenu();
    g.PathConstruction(srcIndex, dstIndex);

    return 0;
}
