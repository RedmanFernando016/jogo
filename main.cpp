#include <iostream>
#include "head.h"
using namespace std;

int main(){

    vector<Mapa> mapas(200);

    Criador(mapas);
    Imprimir(mapas);
    return 0;
}