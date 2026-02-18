#include "head.h"
#include <iostream>
using namespace std; 

void MovimentoJogador(std::vector<Mapa> &mapas){
    bool ValidacaoMovimento = false; 
    char movimento;
    int idx;


    do{    
        cout << "Digite o movimento: \n";
        cin >> movimento;

        for(int i = 0; i < mapas.size(); i++){
            if(mapas[i].bloco == '@');
            idx = i;

            if(movimento == 'w' || movimento =='W'){
                if(mapas[idx - 20].bloco == '|' || idx - 20 < mapas.size()){
                    ValidacaoMovimento = false;
                    cout << "\nMovimento inválido, tente novamente! \n";
                } else {
                    mapas[idx].bloco = '.';
                    mapas[idx - 20].bloco = '@';
                    return;
                }
            }

            if(movimento == 'a' || movimento == 'A'){
                
            }
        }

    } while (ValidacaoMovimento == false);
}

