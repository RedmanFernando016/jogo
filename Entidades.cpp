#include "head.h"
#include <iostream>
using namespace std; 

const int largura = 20;

void MovimentoJogador(std::vector<Mapa> &mapas, std::vector<Item> &inventario, struct Jogador &player){
    bool ValidacaoMovimento = false, ConcluiuMapa = false; 
    char movimento;
    int idx, escolha = 0;
    vector<Item> inventario;


    do{    
        cout << "Digite o movimento: \n";
        cin >> movimento;

        for(int i = 0; i < mapas.size(); i++){
            if(mapas[i].bloco == '@');
            idx = i;
        }

        if(movimento == 'w' || movimento =='W'){
            if(0 <= idx >= 19){
                cout << "Movimento inválido, tente novamente!\n";
                ValidacaoMovimento = false;
                break;
            }

            if(mapas[idx - 20].bloco == '|' || idx - 20 < mapas.size()){
                ValidacaoMovimento = false;
                cout << "\nMovimento inválido, tente novamente! \n";
            } else {
                mapas[idx].bloco = '.';
                mapas[idx - 20].bloco = '@';
                idx = idx - 20;
                ValidacaoMovimento = true;
                return;
            }
        }

        if(movimento == 'a' || movimento == 'A'){
            if(idx % largura == 0){
                cout << "Movimento inválido, tente novamente!\n";
                ValidacaoMovimento = false;
                break;
            }

            if(mapas[idx - 1].bloco == '|' || idx - 1 < mapas.size()){
                ValidacaoMovimento = false;
                cout << "\nMovimento inválido, tente novamente! \n";
            } else {
                mapas[idx].bloco = '.';
                mapas[idx - 1].bloco = '@';
                idx = idx - 1;
                ValidacaoMovimento = true;
                return;
            }
        }

        if(movimento == 's' || movimento == 'S'){
            if(mapas[idx + 20].bloco == '|' || idx + 20 > mapas.size()){
                ValidacaoMovimento = false;
                cout << "\nMovimento inválido, tente novmaente! \n";
            } else if (mapas[idx + 1].bloco == 'Q'){
                ConcluiuMapa = true;
                ValidacaoMovimento = true;
                return; 
            } else {
                mapas[idx].bloco = '.';
                mapas[idx + 20].bloco = '@';
                idx = idx + 20;
                ValidacaoMovimento = true;
                return;
            }
        }

        if(movimento == 'd' || movimento == 'D'){
            if(idx % largura == largura - 1){
                cout << "Movimento inválido, tente novamente!\n";
                ValidacaoMovimento = false;
                break;
            }

            if(mapas[idx + 1].bloco == '|'){
                ValidacaoMovimento = false;
                cout << "\nMovimento inválido, tente novamente! \n";
            } else if (mapas[idx + 1].bloco == 'Q'){
                ConcluiuMapa = true;
                ValidacaoMovimento = true;
                return;                    
            } else {
                mapas[idx].bloco = '.';
                mapas[idx + 1].bloco = '@';
                idx = idx + 1; 
                ValidacaoMovimento = true; 
                return;
            }
        }


        do{
            if(mapas[idx].bloco == '+' || mapas[idx].bloco == 'T'){
                cout << "\n Deseja coletar o item? \n";
                cout << "1 - Sim";
                cout << "2 - Não";
                cin >> escolha;

                if(escolha == 1){
                    if (player.inventario.size() < 3){
                        Item novo = CriarPocao();
                        player.inventario.push_back(novo);
                        cout << "\nItem adicionado\n";
                        ValidacaoMovimento = false;
                    } else {
                        cout << "\nInventário cheio!\n";
                        ValidacaoMovimento = false;
                        break;
                    }
                }
                if(escolha == 2){
                    break;
                    ValidacaoMovimento = false;
                }
                if(escolha != 1 || escolha != 2){
                    cout << "\nOpção inválida, tente novamente!\n";
                }
            } 
        } while(escolha != 1 || escolha != 2);

        if(mapas[idx].bloco == '$'){
            player.dinheiro += mapas[idx].valor; 
        }

        if(movimento == 'c' || movimento == 'C'){
            AbrirInventario(inventario);
            ValidacaoMovimento = false; 
        }

    } while (ValidacaoMovimento == false);
}

void AbrirInventario(std::vector<Item> &inventario){

    cout << "\n-------- INVENTÁRIO --------\n";
    cout << "_"
}

void LargarItem(std::vector<Item> &inventario, const Item &item){

}

Item CriarPocao(){
    Item i; 
    i.nome = "Poção_Cura";
    i.quantidade = 1;
    return i;
}
Item CriarBroca(){
    Item i; 
    i.nome = "Broca";
    i.quantidade = 1;
    return i;
}

