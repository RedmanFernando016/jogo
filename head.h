#ifndef HEAD_H
#define HEAD_H
#include <vector> 

struct Mapa{
    char bloco; 
};

void Criador(std::vector<Mapa> &mapas); 
void Imprimir(std::vector<Mapa> &mapas);

#endif