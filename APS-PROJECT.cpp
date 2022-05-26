#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>
#include<iostream>
#include<list>
#include <string>
#include<vector>
#include<queue>

using namespace std;

int yourchoice,temp=0, srcIndex, dstIndex;
string source, destination;

class Node {
    public:
        string Name;
        string Building;
        int Xpos;
        int Ypos;
        Node () {}
        Node(string Building, string Name,int Xpos, int Ypos) {
            this->Name = Name;
            this->Building = Building;
            this->Xpos = Xpos;
            this->Ypos = Ypos;
        }
};
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

vector<Node> nodeVector;
vector<Edge> edgeList;

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

        void ReadNodeFile(vector<Node>& nodeVector){
            fstream newfile;
            int X,Y;
            newfile.open("nodes.txt",ios::in); //open a file to perform read operation using file object
            if (newfile.is_open()){ //checking whether the file is open
                string tp;
                while(getline(newfile, tp)){ //read data from file object and put it into string.
                    stringstream objX, objY;
                    string building = tp.substr(0,4);
                    string name = tp.substr(tp.find(":")+1,tp.find(";")-5);
                    string Xtemp = tp.substr(tp.find(";")+1,3);
                    objX << Xtemp;
                    objX >> X;
                    string Ytemp = tp.substr(tp.find(",")+1,3);
                    objY << Ytemp;
                    objY >> Y;
                    Node entry(building,name,X,Y);
                    nodeVector.push_back(entry);

                }
                newfile.close(); //close the file object.
            }
        }
        void ReadEdgesFile(vector<Edge>& edgeList){
            fstream newfile;
            int src,dst,weight;
            newfile.open("edges.txt",ios::in); //open a file to perform read operation using file object
            if (newfile.is_open()){ //checking whether the file is open
                string tp;
                while(getline(newfile, tp)){ //read data from file object and put it into string.
                    source = tp.substr(0,tp.find(";"));
                    int len = tp.find(",")-tp.find(";");
                    destination = tp.substr(tp.find(";")+1,len-1);
                    stringstream objS,objD,objW;
                    for(int i = 0; i < nodeVector.size(); i++){
                        if(nodeVector[i].Name == source){
                            src = i+1;
                        }
                        if(nodeVector[i].Name == destination){
                            dst = i+1;
                        }
                    }
                    int len1 = tp.find(".")-tp.find(",")-1;
                    string tempW = tp.substr(tp.find(",")+1,len1);
                    /*cout << source << " ";
                    cout << src << " ";
                    cout << destination << " ";
                    cout << dst << "\t ";
                    cout << tempW << " \t\t ";
                    cout << tp.find(",")<< " ";
                    cout << tp.find(".")<< " ";
                    cout << len1 << endl;*/
                    objW << tempW;
                    objW >> weight;
                    AddEdge(src,dst ,weight);
                }
                newfile.close(); //close the file object.
            }
        }

        Graph (int n) {
            nodes = n;
            distance.resize(n);
            next.resize(n);
            ReadNodeFile(nodeVector);
            ReadEdgesFile(edgeList);

            for (int i=0; i<distance.size(); i++) {
                distance[i].resize(n, 999999999); // 999999999 indicates infinite distance
                next[i].resize(n, -1);
            }
            cout << distance.size() << " " << next.size() << endl;
        }

        void AddEdge (int src, int dst, int weight) {
            Edge f(src, dst, weight);
            edgeList.push_back(f);
            Edge b(dst, src, weight);
            edgeList.push_back(b);
        }

        void Floyd_Warshall() {

            for (int i=0; i<nodes; i++) {
                distance[i][i] = 0;
                next[i][i] = i;
            }
            for(auto& it: edgeList)
                cout<< it.src << " " << it.dst << " " << it.weight << endl;

            cout << distance.size() << " " << next.size() << endl;
            int f = 0;
            for(auto edge: edgeList){
                f++;
                cout << f << endl;
                int u = edge.src;
                //cout << edge.src << " "<< u << "\t";
                int v = edge.dst;
                //cout << edge.dst << " " << v << "\t";
                distance[u][v] = edge.weight;
                next[u][v] = v;
                cout << v << " " << next[u][v] << endl;
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
        }

        // Construct path from source node to destination node
        void PathConstruction (int src, int dst) {

            queue<int> Xqueue,Yqueue,Jqueue;
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

                fstream newfile;
                newfile.open("coordinates.txt", ios::out);
                if (newfile.is_open()){
                    for(auto& it : path){
                        string tp = nodeVector[it-1].Building+";"+to_string(nodeVector[it-1].Xpos)+";"+to_string(nodeVector[it-1].Ypos)+"\n";
                        newfile << tp;
                        cout << nodeVector[it-1].Building << " " << nodeVector[it-1].Name << endl;
                    }
                    newfile.close();
                }

            }

        }


};

Graph g(69);

void Start() {
    //system("clear");
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
    g.ReadEdgesFile(edgeList);

    g.PathConstruction(srcIndex, dstIndex);
    string filename = "./lineDraw.py";
    string command = "python ";
    command += filename;
    system(command.c_str());
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

    g.Floyd_Warshall();
    displaymenu();

    return 0;
}
