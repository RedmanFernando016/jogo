#ifndef HEAD_H
#define HEAD_H
#include <vector> 

struct Mapa{
    char bloco; 
};

// Funções do mapa
void Criador(std::vector<Mapa> &mapas); 
void Imprimir(std::vector<Mapa> &mapas);
void CaminhoGarantido(std::vector<Mapa> &mapas);
void DecidirCaminho(std::vector<Mapa> &mapas, int largura, int &idx, int destino);

//Funções das entidades


#endif