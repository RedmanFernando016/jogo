#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include "head.h"
using namespace std; 

void Criador(std::vector<Mapa> &mapas){
    mapas.resize(200);

    int a, x; 
    bool VerificacaoMapa = true; 

    srand((unsigned) time(nullptr));

    for(int i = 0; i < mapas.size(); i++){
        a = rand(); 

        if(a % 2 == 0){
            mapas[i].bloco = '.'; 
        } else {
            mapas[i].bloco = '|'; 
        }
    }

    mapas[0].bloco = '@'; 
    mapas[199].bloco = 'Q';

    do{ 
        VerificacaoMapa = true;
        
        for(int i = 1; i < mapas.size() - 1; i++){
            if(mapas[i].bloco == '#'){
                a = rand();

                if(a % 2 == 0){
                    mapas[i + 1].bloco = '.'; 
                } else {
                    mapas[i - 1].bloco = '.';
                }
                mapas[i].bloco = '|';
            }
        }

        for(int i = 1; i < mapas.size() - 1; i++){ 
            if(mapas[i + 16].bloco > mapas.size() || mapas[i - 16].bloco < 0){

            } else{
                if(mapas[i].bloco == '|' && mapas[i + 1].bloco == '|' && mapas[i - 1].bloco == '|'){ 
                    VerificacaoMapa = false; 
                    mapas[i].bloco = '#';  
                } 
            }
        } 

        
    } while (VerificacaoMapa == false);
}

void Caminho(std::vector<Mapa> &mapas){
    int a;

    srand((unsigned) time(nullptr));
    a = ran();
    
    mapas[0].bloco = a;
    for(int i = 0; i < mapas.size(); i++){
        
    }
}





void Imprimir(std::vector<Mapa> &mapas){
    int contador = 0;

    cout << "\n";

    for(int i = 0; i < mapas.size(); i++){
        cout << mapas[i].bloco << "  ";
        contador++; 

        if(contador == 20){
            contador = 0;
            cout << "\n";
        }
    }
    cout << "\n";
}