#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include "head.h"
using namespace std; 

const int largura = 20;

void Criador(std::vector<Mapa> &mapas, int &qtde){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    mapas.resize(200);

    int a, x, count = 0; 
    bool VerificacaoMapa = true; 

    for(int i = 0; i < mapas.size(); i++){
        a = rand() % 101; 

        if(a < 25){
            mapas[i].bloco = "."; 
        } else {
            mapas[i].bloco = "|"; 
        }
    }

    mapas[0].bloco = "@"; 
    mapas[199].bloco = "Q";


    VerificacaoMapa = true;
    
    for(int i = 1; i < mapas.size() - 1; i++){
        if(mapas[i].bloco == "#"){
            a = rand();

            if(a % 2 == 0){
                mapas[i + 1].bloco = "."; 
            } else {
                mapas[i - 1].bloco = ".";
            }
            mapas[i].bloco = "|";
        }
    }

    for(int i = 1; i < (int)mapas.size() - 1; i++){
        if(mapas[i].bloco == "|" && mapas[i-1].bloco == "|" && mapas[i+1].bloco == "|"){
            mapas[i].bloco = ".";
        }
    }

    CaminhoGarantido(mapas);

//pos dinheiro ($)
    for(int i = 0; i < mapas.size(); i++){
        a = rand() % 10;

        if(mapas[i].bloco == "."){
            x = rand() % 18;
            if(x < 1){
                mapas[i].bloco = "$";
                mapas[i].valor = a;
            }
        }
    }

//pos. broca (T) - 50%

    bool VerificacaoCasa = false;
    a = rand() % 2;
    
    if(a == 1){
        do{
            a = rand() % 199;

            for(int i = 0; i < mapas.size(); i++){
                if(i == a){
                    if(mapas[i].bloco == "."){
                        mapas[i].bloco = "⛏";
                        VerificacaoCasa = true;
                    }
                }
            }
        } while(VerificacaoCasa == false);
    }
    
    
//pos. cura (+) - 33%

    if(rand() % 3 == 0){
        int qtd = rand() % 3;
        int colocadas = 0;

        for(int tent = 0; tent < 5000 && colocadas < qtd; tent++){
            int pos = rand() % 199;
            
            if(mapas[pos].bloco == "."){
                mapas[pos].bloco = "✚";
                colocadas++;
            }
        }
    }

//pos monstro
    bool ValiMonstro = false;

    a = 0;
    a = rand() % 4;

    if(a < 3){
        int qtde = 0, count = 0, PosMonstro = 0, tent = 0;
        qtde = rand() % 2 + 1;

        do{
            PosMonstro = rand() % 199;
            for(int i = 0; i < mapas.size(); i++){
                if(i == PosMonstro && mapas[i].bloco == "."){
                    mapas[i].bloco = "8";
                    count++;
                }
            }
            if(count == qtde){
                ValiMonstro = true;
            }

            if(tent > 5000){
                break;
            }

            tent++;
        } while (ValiMonstro == false);
    }
}

void CaminhoGarantido(std::vector<Mapa> &mapas){

    int numero;
    vector<int> IntervaloDefinido;

    IntervaloDefinido.reserve(12);

    for(int i = 1; i <= 200; i += 20){
        int j = i + 19;

        if(j > 200){
            j = 200;
        }

        numero = (rand() % (j - i + 1)) + i;
        IntervaloDefinido.push_back(numero);
    }

    IntervaloDefinido.push_back(200);
    
    int idxAtual = 0;

    for(int k = 0; k < IntervaloDefinido.size(); k++){
        int destino = IntervaloDefinido[k] - 1; 

        DecidirCaminho(mapas, largura, idxAtual, destino);
    }
}

void DecidirCaminho(std::vector<Mapa> &mapas, int largura, int &idx, int destino){

    while(idx != destino){
        int linha = idx / largura;
        int coluna = idx % largura;
        int linhaDestino = destino / largura;
        int colunaDestino = destino % largura;


        if(mapas[idx].bloco == "|"){
            mapas[idx].bloco = ".";
        }

        if(linha < linhaDestino){
            idx += largura;
        } else if(linha > linhaDestino){
            idx -= largura;
        } else if(coluna < colunaDestino && coluna < largura - 1){
            idx += 1;
        } else if(coluna > colunaDestino && coluna > 0){
            idx -= 1; 
        }
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