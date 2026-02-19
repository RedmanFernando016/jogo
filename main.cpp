#include <iostream>
#include <time.h>
#include "head.h"
using namespace std;

int main(){
    srand((unsigned) time(nullptr));

    vector<Mapa> mapas(200);

    Criador(mapas);
    Imprimir(mapas);
    return 0;
}