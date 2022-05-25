#include <iostream>
#include <vector>
#include <sstream>
#include <list>
#include <fstream>

using namespace std;
int yourchoice,temp=0, srcIndex,nodes, dstIndex;
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
list<Edge> edgeList;
void AddEdge (int src, int dst, int weight) {
    Edge f(src, dst, weight);
    edgeList.push_back(f);
    Edge b(dst, src, weight);
    edgeList.push_back(b);
}
void ReadNodeFile(vector<Node>& nodeVector){
    fstream newfile;
    int X,Y;
    newfile.open("Nodes.txt",ios::in); //open a file to perform read operation using file object
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
    for(int i = 0; i < nodeVector.size(); i++){
      cout << nodeVector[i].Building << " ";
      cout << nodeVector[i].Name << " ";
      cout << nodeVector[i].Xpos << " ";
      cout << nodeVector[i].Ypos << endl;
      }
}
void ReadEdgesFile(list<Edge>& edgeList){
    fstream newfile;
    int src,dst,weight;
    newfile.open("Edges.txt",ios::in); //open a file to perform read operation using file object
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
            cout << source << " ";
              cout << src << " ";
              cout << destination << " ";
              cout << dst << "\t ";
              cout << tempW << " \t\t ";
              cout << tp.find(",")<< " ";
              cout << tp.find(".")<< " ";
              cout << len1 << endl;
            objW << tempW;
            objW >> weight;
            AddEdge(src,dst ,weight);
        }
        newfile.close(); //close the file object.
    }
    for(auto edge : edgeList){
      cout << edge.src << " ";
      cout << edge.dst << " ";
      cout << edge.weight << endl;
      }
}
vector<vector<int>> Distance,Next;
int n = 89;
void Floyd_Warshall() {
    ReadNodeFile(nodeVector);
    ReadEdgesFile(edgeList);

    nodes = n;
    Distance.resize(n);
    Next.resize(n);

    for (int i=0; i<Distance.size(); i++) {
        Distance[i].resize(n, 999999999); // 999999999 indicates infinite distance
        Next[i].resize(n, -1);
    }

    for (int i=0; i<nodes; i++) {
        Distance[i][i] = 0;
        Next[i][i] = i;
    }
    int f = 0;
    for(auto edge: edgeList){
        f++;
        cout << f << endl;
        int u = edge.src;
        cout << edge.src << " "<< u << "\t";
        int v = edge.dst;
        cout << edge.dst << " " << v << "\t";
        Distance[u][v] = edge.weight;
        cout << Distance[u][v] << endl;
        Next[u][v] = v;
        cout << v << " " << Next[u][v] << endl;
    }
}
int main() {
Floyd_Warshall();
}
