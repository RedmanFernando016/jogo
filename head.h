#ifndef HEAD_H
#define HEAD_H
#include <vector> 
#include <windows.h>
#include <iostream>
using namespace std;

struct Mapa{
    string bloco, blocoAlternativo;
    int valor;
};

struct Item{
    string nome, img;
    int quantidade; 
};

struct Jogador{
    int vida = 100, estamina = 100;
    string ataques;
    double dinheiro = 0.0;

    vector<Item> inventario = vector<Item>(3);
};

struct Monstro{
    int vida = 100, estamina = 100; 
    string ataques; 
    
};

struct MapaCombate{
    string bloco;
};

void Criador(std::vector<Mapa> &mapas, int &qtde);
void Imprimir(std::vector<Mapa> &mapas, struct Jogador &player);
void CaminhoGarantido(std::vector<Mapa> &mapas);
void DecidirCaminho(std::vector<Mapa> &mapas, int largura, int &idx, int destino);

//Funções das entidades



//Mesmo bloco
void MovimentoJogador(std::vector<Mapa> &mapas, struct Jogador &player, vector<Item> &inventario, bool &ConcluiuMapa, int &qtde, std::vector<MapaCombate> &mapacombate, struct Monstro &oponente, bool &derrota);
void AndarDireita(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento, char &movimento, bool &ConcluiuMapa, std::vector<MapaCombate> &mapacombate, struct Monstro &oponente, bool &derrota);
void AndarEsquerda(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, char &movimento, bool &ValidacaoMovimento, std::vector<MapaCombate> &mapacombate, struct Monstro &oponente, bool &derrota);
void AndarCima(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, char &movimento, bool &ValidacaoMovimento, std::vector<MapaCombate> &mapacombate, struct Monstro &oponente, bool &derrota);
void AndarBaixo(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, char &movimento, bool &ValidacaoMovimento, bool &ConcluiuMapa, std::vector<MapaCombate> &mapacombate, struct Monstro &oponente, bool &derrota);
bool QuebrarParede(struct Jogador &player, std::vector<Item> &inventario, std::vector<Mapa> &mapas, char &movimento);
//;


//Mesmo bloco
void AbrirInventario(Jogador &player, std::vector<Item> &inventario, bool &ValidacaoMovimento, std::vector<Mapa> &mapas);
bool AdicionarItem(Jogador &player, const Item &novo);
void LargarItem(Jogador &player, std::vector<Item> &inventari, std::vector<Mapa> &mapas);
void ReorganizarItens(Jogador &player);
//;

void CriadorCombate(std::vector<MapaCombate> &mapacombate);
void ImprimirCombate(std::vector<MapaCombate> &mapacombate);
bool Combate(std::vector<MapaCombate> &mapacombate, struct Jogador &player, struct Monstro &oponente);
void MovimentoMonstro(std::vector<Mapa> &mapas, int &qtdestd, ::vector<MapaCombate> &mapacombate, struct Monstro &oponente, bool &derrota, struct Jogador &player, bool &ValidacaoMovimento);

Item CriarPocao(), CriarBroca();



#endif