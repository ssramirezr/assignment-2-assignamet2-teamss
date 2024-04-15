#include <iostream>
#include <map>

using namespace std;

bool cky(const string& input, const map<string, string>& grammar){

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