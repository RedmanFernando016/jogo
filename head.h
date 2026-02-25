#ifndef HEAD_H
#define HEAD_H
#include <vector> 
#include <windows.h>
using namespace std;

// Funções do mapa

struct Mapa{
    string bloco; 
    int valor;
};

void Criador(std::vector<Mapa> &mapas); 
void Imprimir(std::vector<Mapa> &mapas);
void CaminhoGarantido(std::vector<Mapa> &mapas);
void DecidirCaminho(std::vector<Mapa> &mapas, int largura, int &idx, int destino);


//Funções das entidades

struct Item{
    string nome, img;
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

void MovimentoJogador(std::vector<Mapa> &mapas, struct Jogador &player);
void MovimentoMonstro(std::vector<Mapa> &mapas);
void PegarItem(std::vector<Item> &inventario, const Item &item);
void AbrirInventario(Jogador &player);
void LargarItem(std::vector<Item> &inventario, const Item &item);

void AndarDireita(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial);
void AndarEsquerda(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial);
void AndarCima(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial);
void AndarBaixo(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial);

Item CriarPocao(), CriarBroca();



#endif