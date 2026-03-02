#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string txt, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source;
    source.open(txt);
    string textline;
    while(getline(source,textline)){
        const char *text = textline.c_str();
        char format[] = "%[^:]: %d %d %d";
        int x,y,z;
        int sum ;
        char name[100];
        sscanf(text,format,name,&x,&y,&z);
        sum = x+y+z;
        names.push_back(string(name));
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
    }
    source.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    cin >> command;
    cin.ignore();
    if(toUpperStr(command) == "GRADE" || toUpperStr(command) == "NAME") getline(cin,key);
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    unsigned int count = 0;
    cout << "---------------------------------\n";
    for(unsigned int j = 0; j < scores.size() ;j++){
        if(toUpperStr(names[j]) == key){
            cout << names[j] << "'s score = " << scores[j] << endl;
            cout << names[j] << "'s grade = " << grades[j] << endl;
        }else count++;
    }
    if(count == scores.size()) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    unsigned int count = 0;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < scores.size() ;i++){
        if(string(1,grades[i]) == key){
            cout << names[i] <<" (" << scores[i] << ")\n";
        }else count++;
    }
    if(count == scores.size()) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
