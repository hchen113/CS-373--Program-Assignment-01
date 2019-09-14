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
    
    int start = -1;
    int accept = -1;
    int reject = 1;
    
    ifstream definition_file;
    definition_file.open(filename);
    string line;
    vector<transitions> machine_transations;
    if (definition_file.is_open()){
        while(getline(definition_file, line)){
            //cout << line << "\n";
            int temp_state = -1;
            transitions temp = {-1, 'X', -1, 'X', 'X'};
            string first_word;
            string second_word;
            
            bool first = false;
            for (int i = 0; i < line.length(); i++){
                if (first == false){
                    if (line[i] != '\t' ){
                        first_word.push_back(line[i]);
                    }else{
                        first = true;
                    }
                }else{
                    if (first_word == "state"){
                        if (line[i] == '\t'){
                            continue;
                        }else{
                            if (temp_state == -1){
                                string tempo;
                                while (line[i] != '\t'){
                                    tempo.push_back(line[i]);
                                    i++;
                                }
                                temp_state = stoi(tempo);
                            }else{
                                second_word.push_back(line[i]);
                            }
                            
                            
                        }
                    }else{
                        if (line[i] == '\t'){
                            continue;
                        }else{
                            if (temp.state_1 == -1){
                                string tempo;
                                while (line[i] != '\t'){
                                    tempo.push_back(line[i]);
                                    i++;
                                }
                                //cout << "STATE 1: TEMPO " << tempo << "\n";
                                temp.state_1 = stoi(tempo);
                            }else if (temp.symbol_1 == 'X'){
                                temp.symbol_1 = line[i];
                            }else if (temp.state_2 == -1){
                                string tempo;
                                while (line[i] != '\t'){
                                    tempo.push_back(line[i]);
                                    i++;
                                }
                                //cout << "STATE 2: TEMPO " << tempo << "\n";

                                temp.state_2 = stoi(tempo);
                            }else if (temp.symbol_2 == 'X'){
                                temp.symbol_2 = line[i];
                            }else if (temp.direction == 'X'){
                                temp.direction = line[i];
                            }
                        }
                    }
                }
            }
            if (first_word == "state"){
                if (second_word == "accept"){
                    //cout << " accept " << temp_state << "\n";
                    accept = temp_state;
                }else if (second_word == "reject"){
                    //cout << " reject " << temp_state << "\n";
                    reject = temp_state;
                }else{
                    //cout << " start " << temp_state << "\n";
                    start = temp_state;
                }
            }else{
                machine_transations.push_back(temp);
            }
        }
    }
    
    /* FOR TESTING PURPOSES
    for (int i = 0; i < machine_transations.size(); i++){
        cout << machine_transations[i].state_1 << " " << machine_transations[i].symbol_1 << " " << machine_transations[i].state_2 << " " << machine_transations[i].symbol_2 << " " <<
        machine_transations[i].direction << " \n";
    }
     */
    
    
    
    return 0;
}
