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

//Mesmo bloco
void MovimentoJogador(std::vector<Mapa> &mapas, struct Jogador &player, vector<Item> &inventario);
void AndarDireita(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento);
void AndarEsquerda(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento);
void AndarCima(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento);
void AndarBaixo(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento);
//;

//Mesmo bloco
void AbrirInventario(Jogador &player, std::vector<Item> &inventario, bool &ValidacaoMovimento);
void AdicionarItem(Jogador &player, const Item &novo);
void LargarItem(Jogador &player, std::vector<Item> &inventari);
void ReorganizarItens(Jogador &player);
//;

bool QuebrarParede(Jogador &player, std::vector<Item> &inventario, std::vector<Mapa> &mapas, char &movimento);

void MovimentoMonstro(std::vector<Mapa> &mapas);


Item CriarPocao(), CriarBroca();



#endif