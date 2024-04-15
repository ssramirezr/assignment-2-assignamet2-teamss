#include <iostream>
#include <vector>
#include <map>

using namespace std;

string findInGrammar(const string& prod, const map<string, string>& grammar){
    auto it = grammar.find(prod);
    if(it != grammar.end()){
        return it->second;
    }else{
        return "NA";
    }
}

vector<pair<pair<int,int>, pair<int,int>>> generateSubstrings(int firstIdx, int length){
    vector<pair<pair<int, int>, pair<int, int>>> substrings;
    for(int i=1;i<length;i++){
        int diff = length - i;
        pair<int, int> first = {firstIdx, firstIdx+1};
        pair<int, int> second = {firstIdx+1, firstIdx+diff};
    }
    return substrings;
}

bool cky(const string& input, const map<string, string>& grammar){
    int n = input.size();
    string T[n][n];
    for(int length = 1;length<=n;length++){
        for(int i = 0;i<n-length;i++){
            string val;
            if(length > 1){
                vector<pair<pair<int,int>, pair<int,int>>> subStrings = {}; //generateSubstrings(i, length);
                for(const pair<pair<int,int>, pair<int,int>> subStr: subStrings){
                    int x1 = subStr.first.first;
                    int y1 = subStr.first.first;
                    int x2 = subStr.second.first;
                    int y2 = subStr.second.first;
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
    return 0;
}

int main(){
    int cases; cin >> cases;
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
                for(int i=2;i<production.size()-1;i++){
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
            while(strings--){
                string x; cin >> x;
                if(cky(x, gramatica)){
                    cout << "yes" << endl;
                }else{
                    cout << "no" << endl;
                }
            }
        }
    }
    return 0;
}