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

    Criador(mapas);
    Imprimir(mapas);
    MovimentoJogador(mapas, inventario, player);
    return 0;
}