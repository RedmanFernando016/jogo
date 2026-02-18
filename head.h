#ifndef HEAD_H
#define HEAD_H
#include <vector> 
using namespace std;

// Funções do mapa

struct Mapa{
    char bloco; 
};

void Criador(std::vector<Mapa> &mapas); 
void Imprimir(std::vector<Mapa> &mapas);
void CaminhoGarantido(std::vector<Mapa> &mapas);
void DecidirCaminho(std::vector<Mapa> &mapas, int largura, int &idx, int destino);



//Funções das entidades

struct Item{
    string nome;
    int quantidade;
};

struct Jogador{
    int vida, estamina;
    string ataques;

    vector<Item> inventario;
};

struct Monstro{
    int vida, estamina; 
    string ataques; 
    
};

void MovimentoJogador(std::vector<Mapa> &mapas);
void MovimentoMonstro(std::vector<Mapa> &mapas);
void PegarItem(std::vector<Item> &inventario, const Item &item);
void AbrirInventario(std::vector<Item> &inventario, const Item &item);
void LargarItem(std::vector<Item> &inventario, const Item &item);



#endif