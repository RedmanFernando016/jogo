#include <iostream>
#include <time.h>
#include <windows.h>
#include "head.h"
using namespace std;

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    bool ValidacaoMovimento = false; 
    srand((unsigned) time(nullptr));

    vector<Mapa> mapas(200);
    vector<Item> inventario;
    Jogador player;
    bool Vitoria = false;
    int count = 0, qtde = 0; 

    do{
        bool ConcluiuMapa = false;
        cout << "\n[DEBUG] Gerando mapa...\n";
        Criador(mapas, qtde);
        cout << "[DEBUG] Mapa gerado!\n";

        do{
            Imprimir(mapas);
            MovimentoJogador(mapas, player, inventario, ConcluiuMapa, qtde);
        } while(ConcluiuMapa == false);

    } while(Vitoria == false);

    return 0;
}