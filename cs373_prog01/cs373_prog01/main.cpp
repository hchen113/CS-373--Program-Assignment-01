#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct transitions{
    int state_1;
    char symbol_1;
    int state_2;
    char symbol_2;
    char direction;
};

int main(int argc, char *argv[]){
    
    if (argc != 4){
        cout << "ERROR WITH INPUT \n";
        exit(1);
    }
    string filename = argv[1];
    string input = argv[2];
    int trans_num = stoi(argv[3]);
    
    int start, accept, reject;
    
    
    
    
    
    
    
    return 0;
}
