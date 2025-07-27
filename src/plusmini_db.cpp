#include <iostream>
using namespace std;

int main(int argc, char * argv[]){
    if(argc < 2){
        cout << "You should provide a file name" << endl;
        cout << "argc: " << argc << endl;
    }
    cout << argv[1] << endl;

    return 0;
}