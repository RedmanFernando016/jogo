#include <iostream>
#include <time.h>
#include <windows.h>
#include "head.h"
using namespace std;

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    bool ValidacaoMovimento = false, ConcluiuMapa = false; 
    srand((unsigned) time(nullptr));

    vector<Mapa> mapas(200);
    vector<Item> inventario;
    Jogador player;
    bool Terminar = false, Vitoria = false;
    int count = 0; 

    do{
        Criador(mapas);

        do{
            Imprimir(mapas);
            MovimentoJogador(mapas, player, inventario);
        } while(Terminar == false);

    } while(Vitoria == false);

    return 0;
}