#include <iostream>
#include <vector>
#include <map>

using namespace std;

string findInGrammar(const string& prod, const map<string, string>& grammar){
    auto it = grammar.find(prod);
    return it != grammar.end() ? it->second : "NA";
}

vector<pair<pair<int,int>, pair<int,int>>> generateSubstrings(int firstIdx, int length){
    vector<pair<pair<int, int>, pair<int, int>>> subStrings;
    for(int i=1;i<length;i++){
        pair<int, int> first = {firstIdx, firstIdx+i};
        pair<int, int> second = {firstIdx+i, firstIdx+length};
        pair<pair<int, int>, pair<int, int>> couple = {first, second};
        subStrings.push_back(couple);
    }
    return subStrings;
}

bool cky(const string& input, const map<string, string>& grammar){
    int n = input.size()+1;
    string T[n][n];
    for(int length = 1;length<n;length++){
        int res = n-length;
        for(int i = 0;i<res;i++){
            string val;
            if(length > 1){
                vector<pair<pair<int,int>, pair<int,int>>> subStrings = generateSubstrings(i, length);
                for(const pair<pair<int,int>, pair<int,int>> subStr: subStrings){
                    int x1 = subStr.first.first;
                    int y1 = subStr.first.second;
                    int x2 = subStr.second.first;
                    int y2 = subStr.second.second;
                    string prod = T[x1][y1] + T[x2][y2];
                    val = findInGrammar(prod, grammar);
                    if(val != "NA") break;
                }
            }else{
                val = findInGrammar(input.substr(i, 1), grammar);
            }
            T[i][i+length] = val;
        }
    }
    return T[0][n-1] == "S" ? true : false;
}

int main(){
    int cases; cin >> cases;
    string output;
    while(cases--){
        int gLines; cin >> gLines; //Lineas de gramática
        int strings; cin >> strings; //Cadenas a analizar
        map<string, string> gramatica; //Diccionario que va a tener la gramatica.
        cin.ignore();
        while(gLines--){
            string production; getline(cin, production);
            string head = production.substr(0,1);
            string derivate;
            if(production.size() == 3){
                derivate = production.substr(2,1);
                gramatica[derivate] = head;
            }else{
                for(int i=2;i<production.size();i++){
                    if(production[i] == ' ') continue;
                    if(production[i+1] != ' '){
                        derivate = production.substr(i,2);
                        i++;
                    }else{
                        derivate = production.substr(i,1);
                    }
                    gramatica[derivate] = head;
                }
            }
        }
        while(strings--){
            string x; cin >> x;
            if(cky(x, gramatica)){
                // cout << "yes" << endl;
                output += "yes\n";
            }else{
                // cout << "no" << endl;
                output += "no\n";
            }
        }
    }
    cout << output << endl;
    return 0;
}