#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Node{
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

int main() {
    list<Edge> edgeList;
    std::vector<Node> nodeVector;
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

    int src=0,dst=0,weight;
    string source, destination;
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
            /*cout << source << " ";
            cout << src << " ";
            cout << destination << " ";
            cout << dst << "\t ";
            cout << tempW << " \t\t ";
            cout << tp.find(",")<< " ";
            cout << tp.find(".")<< " ";
            cout << len1 << endl;*/
            string tempW = tp.substr(tp.find(",")+1,len1);
            objW << tempW;
            objW >> weight;
            Edge forward(src, dst, weight);
            edgeList.push_back(forward);
            Edge backward(dst, src, weight);
            edgeList.push_back(backward);
        }
        newfile.close(); //close the file object.
    }
    for(auto edge : edgeList){
        cout << edge.src << " ";
        cout << edge.dst << " ";
        cout << edge.weight << endl;
      }
}
