#include "head.h"
#include <iostream>
#include <vector>
#include <limits>
#include <windows.h>

using namespace std; 

void CriadorCombate(std::vector<MapaCombate> &mapacombate){
    mapacombate.resize(24);

    for(int i = 0; i < mapacombate.size(); i++){
        mapacombate[i].bloco = ".";
    }

    mapacombate[10].bloco = "@";
    mapacombate[15].bloco = "8";
}

void ImprimirCombate(std::vector<MapaCombate> &mapacombate){
    int count = 0;

    for(int i = 0; i < mapacombate.size(); i++){
        cout << " " << mapacombate[i].bloco << " ";
        count++;

        if(count == 8){
            cout << "\n";
            count = 0;
        }
    }
    cout << "\n";
}

bool Combate(std::vector<MapaCombate> &mapacombate, struct Jogador &player, struct Monstro &oponente){
    int acao = 0;
    bool verificacao = false;

    oponente.vida = 100;
    oponente.estamina = 100;
    player.estamina = 100;

    do {
        player.estamina += 30;
        if(player.estamina > 100){
            player.estamina = 100;
        }

//atqaue player
        do{
            system("cls");
            cout << "       LUTA       \n";
            CriadorCombate(mapacombate);
            ImprimirCombate(mapacombate);
            cout << "1 - Soco    2 - Chute    3 - Picaretada    4 - Curar    5 - Defender\n";  
            acao = 0;
            
            while (!(cin >> acao)) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\nEntrada inválida. Digite um número: \n";
            }

            if(acao < 1 || acao > 5){
                cout << "\noperação inválida, tente novamente!\n";
                verificacao = false;
            }

            if(acao == 1){
                if(player.estamina < 20){
                    cout << "Sem estamina\n";
                    verificacao = false;
                } else {
                    oponente.vida -= 20;
                    player.estamina -= 20;
                    cout << "\nVocê ataca com um soco poderoso!\n";
                    verificacao = true;
                }
            }

            if(acao == 2){
                if(player.estamina < 30){
                    cout << "\nSem estamina\n";
                    verificacao = false;
                } else {
                    oponente.vida -= 30;
                    player.estamina -= 30;
                    cout << "\nVocê ataca com um chute poderoso!\n";
                    verificacao = true;
                }
            }

            if(acao == 3){
                if(player.estamina >= 60){
                    int idx = 0;
                    bool validacao = false;

                    for(int i = 0; i < 3; i++){
                        if(player.inventario[i].img == "⛏"){
                            idx = i;
                            validacao = true;
                            cout << "\nVocê quebra a broca na cabeça do monstro!\n";
                            break;
                        }
                    }

                    if(validacao == true){
                        oponente.vida -= 75;
                        player.inventario[idx].nome = "";
                        player.inventario[idx].img = "";
                        ReorganizarItens(player);

                        player.estamina -= 60;
                        verificacao = true;
                    }

                    if(validacao == false){
                        cout << "Sem Picaretas no inventário!\n";
                        verificacao = false;
                    }
                } else {
                    cout << "Sem estamina!\n";
                    verificacao = false;
                }   
            }

            if(acao == 4){
                int idx = 0;
                bool validacao = false;


                for(int i = 0; i < 3; i++){
                    if(player.inventario[i].img == "✚"){
                        idx = i;
                        validacao = true;
                        break;
                    }
                }

                if(validacao == true){
                    cout << "\nCurando...";
                    Sleep(2000);

                    player.vida += 80;
                    if(player.vida > 100){
                        player.vida = 100;
                    }
                    
                    verificacao = true;
                    player.inventario[idx].nome = "";
                    player.inventario[idx].img = "";
                    ReorganizarItens(player);
                }
                
                if(validacao == false){
                    cout << "Sem curas no inventario!\n";
                    verificacao = false;
                }     
            }

            if(acao == 5){
                verificacao = true;
            }

        } while(verificacao == false);

        if(player.vida >= 1 && oponente.vida <= 0){
            return true;
        }

//ataque do monstrp
        int AtaqueOponente = 0;
        AtaqueOponente = rand() % 2;

        if(AtaqueOponente == 0){
            if(acao == 5){
                int a = 0;
                a = rand() % 100;

                if(a <= 49){
                    cout << "Oponente ataca com um soco poderoso, porém é bloqueado!\n";
                } else {
                    cout << "Oponente ataca com um soco poderoso que quebra o bloqueio do jogador!\n";
                    cout << "-10 HP\n";
                    player.vida -= 10;
                }
            } else{ 
                cout << "Oponente ataca com um soco poderoso!\n";
                cout << "-10 HP\n";
                player.vida -= 10;
            }
        }
        
        if(AtaqueOponente == 1){
            if(acao == 5){
                int a = 0;
                a = rand() % 100;

                if(a <= 49){
                    cout << "Oponente ataca com um chute veloz, porém é bloqueado!\n";
                } else {
                    cout << "Oponente Ataca com um chute veloz que é capaz de quebrar o bloqueio do jogador!\n";
                    cout << "-15 HP\n";
                    player.vida -= 15;
                }
            } else {
                cout << "Oponente Ataca com um chute veloz!\n";
                cout << "-15 HP\n";
                player.vida -= 15;
            }
            
        }

        if(player.vida <= 0 && oponente.vida >= 1){
            return false;
        }

    } while(player.vida < 50000);
}