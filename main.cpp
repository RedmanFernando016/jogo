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
    vector<MapaCombate> mapacombate;
    Monstro oponente;
    Jogador player;

    bool Derrota = false;
    int count = 0, qtde = 0; 

    do{
        bool ConcluiuMapa = false;
        cout << "\n[DEBUG] Gerando mapa...\n";
        Criador(mapas, qtde);
        cout << "[DEBUG] Mapa gerado!\n";

        do{
            system("cls");
            Imprimir(mapas, player);
            MovimentoJogador(mapas, player, inventario, ConcluiuMapa, qtde, mapacombate, oponente, Derrota);
        } while(ConcluiuMapa == false);

    } while(Derrota == false);

    return 0;
}