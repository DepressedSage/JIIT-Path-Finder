#include <iostream>
#include <vector>
using namespace std;

void help(vector<int> A) {
    for(int i = 0; i < A.size(); i++){
        A.push_back(0);
    }
}

void P(vector<int> A) {
    int i;
    for (i = 0; i < A.size(); ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}
int main() {
    vector<int> vec = {4,5,6,7,2,6};
    for(int i = 0; i < vec.size(); i++){
        vec.push_back(3);
    }

}
