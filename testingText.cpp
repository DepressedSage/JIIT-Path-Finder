#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

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
int main() {
    vector<Node> nodeVector;
    fstream newfile;
    int X,Y;
    newfile.open("test.txt",ios::in); //open a file to perform read operation using file object
   if (newfile.is_open()){ //checking whether the file is open
      string tp;
      while(getline(newfile, tp)){ //read data from file object and put it into string.
    stringstream objX, objY;
          string name = tp.substr(0,tp.find(":"));
          string Xtemp = tp.substr(tp.find(":")+1,1);
          cout << Xtemp << endl;
          objX << Xtemp;
          objX >> X;
          string Ytemp = tp.substr(tp.find(";")+1,1);
          cout << Ytemp << endl;
          objY << Ytemp;
          objY >> Y;
          Node entry(name,X,Y);
          nodeVector.push_back(entry);

        }
      newfile.close(); //close the file object.
   }
   for(int i = 0; i < nodeVector.size(); i++){
       cout << nodeVector[i].Name << endl;
       cout << nodeVector[i].Xpos << endl;
       cout << nodeVector[i].Ypos << endl;
   }
}
