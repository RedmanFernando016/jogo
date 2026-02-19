#ifndef HEAD_H
#define HEAD_H
#include <vector> 
using namespace std;

// Funções do mapa

struct Mapa{
    char bloco; 
    int valor;
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
    double dinheiro = 0.0;

    vector<Item> inventario = vector<Item>(3);
};

struct Monstro{
    int vida, estamina; 
    string ataques; 
    
};

void MovimentoJogador(std::vector<Mapa> &mapas, std::vector<Item> &inventario, struct Jogador &player);
void MovimentoMonstro(std::vector<Mapa> &mapas);
void PegarItem(std::vector<Item> &inventario, const Item &item);
void AbrirInventario(std::vector<Item> &inventario);
void LargarItem(std::vector<Item> &inventario, const Item &item);
Item CriarPocao(), CriarBroca();



#endif