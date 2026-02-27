#ifndef HEAD_H
#define HEAD_H
#include <vector> 
#include <windows.h>
#include <iostream>
using namespace std;

// Funções do mapa

struct Mapa{
    string bloco, blocoAlternativo; 
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
void AbrirInventario(std::vector<Mapa> &mapas, Jogador &player, int &idx);
void AdicionarItem(Jogador &player, const Item &novo);
void LargarItem(std::vector<Mapa> &mapas, Jogador &player, const Item &item, int &idx);

void AndarDireita(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento);
void AndarEsquerda(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento);
void AndarCima(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento);
void AndarBaixo(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento);

Item CriarPocao(), CriarBroca();



#endif