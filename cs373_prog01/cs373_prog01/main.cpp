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

struct result{
    string end_phase;
    vector<int> state;
};

result run_turing_machine(vector<transitions> machine_transitions, int start, int accept, int reject, string input_str, int trans_num){
    result solution;
    string input;
    for (int i = 0; i < input_str.length(); i++){
        if (input_str[i] == '_'){
            input.push_back(' ');
            continue;
        }
        input.push_back(input_str[i]);
    }
    
    //cout << "FINISH CONVERTING INPUT. \n";
    //cout << input << "\n";
    bool done = false;
    int char_count = 0;
    int state = start;
    int transition_count = 0;
    
    while (done != true){
        
        //cout << "TRANSITION COUNT: " << transition_count << "\n";
        //cout << "Current State: " << state << " with char: " << input[char_count] << "\n";
        for (int i = 0; i < machine_transitions.size(); i++){
            if(machine_transitions[i].state_1 == state && machine_transitions[i].symbol_1 == input[char_count]){
                if (machine_transitions[i].state_2 == accept){
                    state = accept;
                    solution.state.push_back(accept);
                    solution.end_phase = "accept";
                    done = true;
                    //cout << "ACCEPT AT STATE " << state << "\n";
                    break;
                }
                if (machine_transitions[i].state_2 == reject){
                    state = reject;
                    solution.state.push_back(reject);
                    solution.end_phase = "reject";
                    done = true;
                    //cout << "REJECT AT STATE " << state << "\n";
                    break;
                }
                if (transition_count > trans_num){
                    //state = machine_transitions[i].state_2;
                    //solution.state.push_back(state);
                    solution.end_phase = "quit";
                    done = true;
                    //cout << "QUIT AT STATE " << state << "\n";
                    break;
                }
                solution.state.push_back(state);
                state = machine_transitions[i].state_2;
                //cout << "TRANSITIONING TO STATE " << state << " , REPLACING " << input[char_count];
                input[char_count] = machine_transitions[i].symbol_2;
                //cout << " WITH " << input[char_count] << "\n";
                if (machine_transitions[i].direction == 'L'){
                    //cout << "SHIFTING L \n";
                    char_count --;
                    //cout << "CHAR COUNT: " << char_count << "\n";
                }else{
                    //cout << "SHIFTING R \n";
                    char_count ++;
                    //cout << "CHAR COUNT: " << char_count << "\n";
                }
                break;
            }
        }
        transition_count ++;
    }
    
    
    return solution;
}

int main(int argc, char *argv[]){
    
    if (argc != 4){
        cerr << "ERROR WITH INPUT \n";
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
        //cout << "OPENING DEFINTION FILE" << "\n";
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
                                if (line[i] == '_'){
                                    temp.symbol_1 = ' ';
                                }else{
                                    temp.symbol_1 = line[i];
                                }
                            }else if (temp.state_2 == -1){
                                string tempo;
                                while (line[i] != '\t'){
                                    tempo.push_back(line[i]);
                                    i++;
                                }
                                //cout << "STATE 2: TEMPO " << tempo << "\n";

                                temp.state_2 = stoi(tempo);
                            }else if (temp.symbol_2 == 'X'){
                                if (line[i] == '_'){
                                    temp.symbol_2 = ' ';
                                }else{
                                    temp.symbol_2 = line[i];
                                }
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
    }*/

    
    //cout << "DONE WITH ANALZYING INPUT FILE. \n";
    
    result temp = run_turing_machine(machine_transations, start, accept, reject, input, trans_num);
    
    
    for (int i = 0; i < temp.state.size(); i++){
        cout << temp.state[i];
        if (i < temp.state.size() -1){
            cout << "->";
        }
    }
    cout << " " << temp.end_phase << "\n";
    
    
    
    return 0;
}
