#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

int main() {
    std::queue<int> Xqueue, Yqueue ;
    Xqueue.push(5);Yqueue.push(6);
    Xqueue.push(3);Yqueue.push(6);
    Xqueue.push(5);Yqueue.push(4);
    Xqueue.push(2);Yqueue.push(8);
    Xqueue.push(8);Yqueue.push(0);
                fstream newfile;
                newfile.open("Quardinates.txt", ios::out);
                if (newfile.is_open()){
                    while(!Xqueue.empty()){
                    string tp = to_string(Xqueue.front())+";"+to_string(Yqueue.front())+"\n";
                    newfile << tp;
                    Xqueue.pop();Yqueue.pop();}
                    newfile.close();
                }
}
