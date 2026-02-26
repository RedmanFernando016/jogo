#include "head.h"
#include <iostream>
using namespace std; 

string BlocoEspecial = "nulo";
const int largura = 20;

void MovimentoJogador(std::vector<Mapa> &mapas, struct Jogador &player){
    bool ValidacaoMovimento = false, ConcluiuMapa = false; 
    char movimento;
    int idx, escolha = 0;

    do{    
        cout << "Digite o movimento: \n";
        cin >> movimento;

        for(int i = 0; i < mapas.size(); i++){
            if(mapas[i].bloco == "@"){
                idx = i;
                break;
            }
        }

        if(movimento == 'd' || movimento == 'D'){
            AndarDireita(mapas, player, idx, BlocoEspecial, ValidacaoMovimento);
        } else if (movimento == 'a' || movimento == 'A'){
            AndarEsquerda(mapas, player, idx, BlocoEspecial, ValidacaoMovimento);
        } else if (movimento == 'w' || movimento == 'W'){
            AndarCima (mapas, player, idx, BlocoEspecial, ValidacaoMovimento);
        } else if (movimento == 's' || movimento == 'S'){
            AndarBaixo(mapas, player, idx, BlocoEspecial, ValidacaoMovimento);
        } else if (movimento == 'c' || movimento == 'C'){
            AbrirInventario(player); 
        } 


    } while (ValidacaoMovimento == false);
}

void AbrirInventario(Jogador &player){

    cout << " ┌──────────────────────┐\n";
    cout << " |                      |\n";
    cout << " |      INVENTÁRIO      |\n";
    cout << " |______________________|\n";
    cout << " |        Itens         |\n";
    cout << " |                      |\n";

    for(int i = 0; i < 3; i++){
        if(player.inventario[i].img == "⛏"){
            cout << " | [⛏] - Picareta       |\n"; 
        } else if (player.inventario[i].img == "✚"){
            cout << " | [✚] - Poção de cura  |\n";
        } else {
            cout << " | [ ] - ...            |\n";
        }
    }
    cout << " |                      |\n";
    cout << " └──────────────────────┘\n";
}

void AdicionarItem(Jogador &player, const Item &novo){
    for(int i = 0; i < 3; i++){
        if (player.inventario[i].nome == ""){
            player.inventario[i] = novo;
            return;
        }
    }
    cout << "Sem espaço no inventário!\n";
    return;
}

void LargarItem(Jogador &player){

}

Item CriarPocao(){
    Item i; 
    i.nome = "Poção de Cura";
    i.quantidade = 1;
    i.img = "✚";
    return i;
}
Item CriarBroca(){
    Item i; 
    i.nome = "Broca";
    i.quantidade = 1;
    i.img =  "⛏";
    return i;
}


void AndarDireita(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento){
    bool ConcluiuMapa = false; 
    int escolha = 0;
    vector<Item> inventario;
    
    
    if(idx % largura == largura - 1){
        cout << "Movimento inválido, tente novamente!\n";
        ValidacaoMovimento = false;
        return;
    }

    if(mapas[idx + 1].bloco == "|"){
        ValidacaoMovimento = false;
        cout << "\nMovimento inválido, tente novamente! \n";

    } else if(mapas[idx + 1].bloco == "Q"){
        ConcluiuMapa = true;
        ValidacaoMovimento = true;
        return;

    } else if(BlocoEspecial != "nulo"){
        if(BlocoEspecial == "✚"){
            mapas[idx].bloco = "✚"; 
            if(mapas[idx + 1].bloco == "$"){
                idx = idx + 1;
                player.dinheiro += mapas[idx].valor; 
                mapas[idx].bloco = "@";
                ValidacaoMovimento = true;
                BlocoEspecial = "nulo";
                return;
            } else {
                mapas[idx + 1].bloco = "@";
                BlocoEspecial = "nulo";
                ValidacaoMovimento = true;
                idx = idx + 1;
                return;
            }
        } else {
            mapas[idx].bloco = "⛏";
            if(mapas[idx + 1].bloco == "$"){
                idx = idx + 1;
                player.dinheiro += mapas[idx].valor; 
                mapas[idx].bloco = "@";
                ValidacaoMovimento = true;
                BlocoEspecial = "nulo";
                return;
            } else {
                mapas[idx + 1].bloco = "@";
                BlocoEspecial = "nulo";
                ValidacaoMovimento = true;
                idx = idx + 1;
                return; 
            }
        }

    } else if(mapas[idx + 1].bloco == "✚" || mapas[idx + 1].bloco == "⛏"){
        BlocoEspecial = mapas[idx + 1].bloco;
        mapas[idx].bloco = ".";
        mapas[idx + 1].bloco = "@";
        idx = idx + 1; 
        ValidacaoMovimento = true; 
        //Nota: Não colcoar return, se verdadeiro, vai cair na função de baixo

    } else if (mapas[idx + 1].bloco == "$"){
        mapas[idx].bloco = ".";
        idx = idx + 1;
        mapas[idx].bloco = "@";                
        player.dinheiro += mapas[idx].valor; 
        return;

    } else {
        mapas[idx].bloco = ".";
        mapas[idx + 1].bloco = "@";
        idx = idx + 1;
        ValidacaoMovimento = true; 
        return;
    }


    do{
        if(BlocoEspecial == "✚" || BlocoEspecial == "⛏"){
            cout << "\n Deseja coletar o item? \n";
            cout << "1 - Sim";
            cout << "2 - Não";
            cin >> escolha;

            if(escolha == 1){
                if(BlocoEspecial == "✚"){
                    Item novo = CriarPocao();
                    AdicionarItem(player, novo);
                    cout << "\nPoção de cura adicionado ao inventário!\n";
                    ValidacaoMovimento = true;
                    BlocoEspecial = "nulo";
                    return;
                } else {
                    Item novo = CriarBroca();
                    AdicionarItem(player, novo);
                    cout << "\nBroca adicionada ao inventário!\n";
                    ValidacaoMovimento = true;
                    BlocoEspecial = "nulo";
                    return;
                }
        }
            if(escolha == 2){
                ValidacaoMovimento = true;
                return;
            }
            if(escolha < 1 || escolha > 2){
                cout << "\nOpção inválida, tente novamente!\n";
            }
        } 
    } while(escolha < 1 || escolha > 2);

}

void AndarEsquerda(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento){
    bool ConcluiuMapa = false; 
    char movimento;
    int escolha = 0;
    vector<Item> inventario;


    if(idx % largura == 0){
        cout << "Movimento inválido, tente novamente!\n";
        ValidacaoMovimento = false;
        return;
    }

    if(mapas[idx - 1].bloco == "|"){
        ValidacaoMovimento = false;
        cout << "\nMovimento inválido, tente novamente! \n";

    } else if(BlocoEspecial != "nulo"){
        if(BlocoEspecial == "✚"){
            mapas[idx].bloco = "✚"; 
            if(mapas[idx - 1].bloco == "$"){
                idx = idx - 1;
                player.dinheiro += mapas[idx].valor; 
                mapas[idx].bloco = "@";
                ValidacaoMovimento = true;
                BlocoEspecial = "nulo";
                return;
            } else {
                mapas[idx - 1].bloco = "@";
                BlocoEspecial = "nulo";
                ValidacaoMovimento = true;
                idx = idx - 1;
                return;
            }
        } else {
            mapas[idx].bloco = "⛏";
            if(mapas[idx - 1].bloco == "$"){
                idx = idx - 1;
                player.dinheiro += mapas[idx].valor; 
                mapas[idx].bloco = "@";
                ValidacaoMovimento = true;
                BlocoEspecial = "nulo";
                return;
            } else {
                mapas[idx - 1].bloco = "@";
                BlocoEspecial = "nulo";
                ValidacaoMovimento = true;
                idx = idx - 1;
                return; 
            }
        }

    } else if(mapas[idx - 1].bloco == "✚" || mapas[idx - 1].bloco == "⛏"){
        BlocoEspecial = mapas[idx - 1].bloco;
        mapas[idx].bloco = ".";
        mapas[idx - 1].bloco = "@";
        idx = idx - 1; 
        ValidacaoMovimento = true; 
        //Nota: Não colcoar return, se verdadeiro, vai cair na função de baixo

    } else if (mapas[idx - 1].bloco == "$"){
        mapas[idx].bloco = ".";
        idx = idx - 1;
        mapas[idx].bloco = "@";                
        player.dinheiro += mapas[idx].valor; 
        return;

    } else {
        mapas[idx].bloco = ".";
        mapas[idx - 1].bloco = "@";
        idx = idx - 1;
        ValidacaoMovimento = true; 
        return;
    }

    do{
        if(BlocoEspecial == "✚" || BlocoEspecial == "⛏"){
            cout << "\n Deseja coletar o item? \n";
            cout << "1 - Sim";
            cout << "2 - Não";
            cin >> escolha;

            if(escolha == 1){
                if(BlocoEspecial == "✚"){
                    Item novo = CriarPocao();
                    AdicionarItem(player, novo);
                    cout << "\nPoção de cura adicionado ao inventário!\n";
                    ValidacaoMovimento = true;
                    BlocoEspecial = "nulo";
                    return;
                } else {
                    Item novo = CriarBroca();
                    AdicionarItem(player, novo);
                    cout << "\nBroca adicionada ao inventário!\n";
                    ValidacaoMovimento = true;
                    BlocoEspecial = "nulo";
                    return;
                }
            }
            if(escolha == 2){
                ValidacaoMovimento = true;
                return;
            }
            if(escolha < 1 || escolha > 2){
                cout << "\nOpção inválida, tente novamente!\n";
            }
        } 
    } while(escolha < 1 || escolha > 2);
}

void AndarCima(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento){
    bool ConcluiuMapa = false; 
    char movimento;
    int escolha = 0;
    vector<Item> inventario;


    if(idx < largura){
        cout << "Movimento inválido, tente novamente!\n";
        ValidacaoMovimento = false;
        return;
    }

    if(mapas[idx - 20].bloco == "|"){
        ValidacaoMovimento = false;
        cout << "\nMovimento inválido, tente novamente! \n";

    } else if(BlocoEspecial != "nulo"){
        if(BlocoEspecial == "✚"){
            mapas[idx].bloco = "✚"; 
            if(mapas[idx - 20].bloco == "$"){
                idx = idx - 20;
                player.dinheiro += mapas[idx].valor; 
                mapas[idx].bloco = "@";
                ValidacaoMovimento = true;
                BlocoEspecial = "nulo";
                return;
            } else {
                mapas[idx - 20].bloco = "@";
                BlocoEspecial = "nulo";
                ValidacaoMovimento = true;
                idx = idx - 20;
                return;
            }
        } else {
            mapas[idx].bloco = "⛏";
            if(mapas[idx - 20].bloco == "$"){
                idx = idx - 20;
                player.dinheiro += mapas[idx].valor; 
                mapas[idx].bloco = "@";
                ValidacaoMovimento = true;
                BlocoEspecial = "nulo";
                return;
            } else {
                mapas[idx - 20].bloco = "@";
                BlocoEspecial = "nulo";
                ValidacaoMovimento = true;
                idx = idx - 1;
                return; 
            }
        }

    } else if(mapas[idx - 20].bloco == "✚" || mapas[idx - 20].bloco == "⛏"){
        BlocoEspecial = mapas[idx - 20].bloco;
        mapas[idx].bloco = ".";
        mapas[idx - 20].bloco = "@";
        idx = idx - 20; 
        ValidacaoMovimento = true; 
        //Nota: Não colcoar return, se verdadeiro, vai cair na função de baixo

    } else if (mapas[idx - 20].bloco == "$"){
        mapas[idx].bloco = ".";
        idx = idx - 20;
        mapas[idx].bloco = "@";                
        player.dinheiro += mapas[idx].valor; 
        return;

    } else {
        mapas[idx].bloco = ".";
        mapas[idx - 20].bloco = "@";
        idx = idx - 20;
        ValidacaoMovimento = true; 
        return;
    }

    do{
        if(BlocoEspecial == "✚" || BlocoEspecial == "⛏"){
            cout << "\n Deseja coletar o item? \n";
            cout << "1 - Sim";
            cout << "2 - Não";
            cin >> escolha;

            if(escolha == 1){
                if(BlocoEspecial == "✚"){
                    Item novo = CriarPocao();
                    AdicionarItem(player, novo);
                    cout << "\nPoção de cura adicionado ao inventário!\n";
                    ValidacaoMovimento = true;
                    BlocoEspecial = "nulo";
                    return;
                } else {
                    Item novo = CriarBroca();
                    AdicionarItem(player, novo);
                    cout << "\nBroca adicionada ao inventário!\n";
                    ValidacaoMovimento = true;
                    BlocoEspecial = "nulo";
                    return;
                }
            }
            if(escolha == 2){
                ValidacaoMovimento = true;
                return;
            }
            if(escolha < 1 || escolha > 2){
                cout << "\nOpção inválida, tente novamente!\n";
            }
        } 
    } while(escolha < 1 || escolha > 2);
}

void AndarBaixo(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento){
    bool ConcluiuMapa = false; 
    char movimento;
    int escolha = 0;
    vector<Item> inventario;

    if(mapas[idx + 20].bloco == "|" || idx + largura >= mapas.size()){
        ValidacaoMovimento = false;
        cout << "\nMovimento inválido, tente novamente! \n";
        return;
    } else if(mapas[idx + 20].bloco == "Q"){
        ConcluiuMapa = true;
        ValidacaoMovimento = true;
        return;
    } else if(BlocoEspecial != "nulo"){
        if(BlocoEspecial == "✚"){
            mapas[idx].bloco = "✚"; 
            if(mapas[idx + 20].bloco == "$"){
                idx = idx + 20;
                player.dinheiro += mapas[idx].valor; 
                mapas[idx].bloco = "@";
                ValidacaoMovimento = true;
                BlocoEspecial = "nulo";
                return;
            } else {
                mapas[idx + 20].bloco = "@";
                BlocoEspecial = "nulo";
                ValidacaoMovimento = true;
                idx = idx + 20;
                return;
            }
        } else {
            mapas[idx].bloco = "⛏";
            if(mapas[idx + 20].bloco == "$"){
                idx = idx + 20;
                player.dinheiro += mapas[idx].valor; 
                mapas[idx].bloco = "@";
                ValidacaoMovimento = true;
                BlocoEspecial = "nulo";
                return;
            } else {
                mapas[idx + 20].bloco = "@";
                BlocoEspecial = "nulo";
                ValidacaoMovimento = true;
                idx = idx + 20;
                return; 
            }
        }

    } else if(mapas[idx + 20].bloco == "✚" || mapas[idx + 20].bloco == "⛏"){
        BlocoEspecial = mapas[idx + 20].bloco;
        mapas[idx].bloco = ".";
        mapas[idx + 20].bloco = "@";
        idx = idx + 20; 
        ValidacaoMovimento = true; 
        //Nota: Não colcoar return, se verdadeiro, vai cair na função de baixo

    } else if (mapas[idx + 20].bloco == "$"){
        mapas[idx].bloco = ".";
        idx = idx + 20;
        mapas[idx].bloco = "@";                
        player.dinheiro += mapas[idx].valor; 
        return;

    } else {
        mapas[idx].bloco = ".";
        mapas[idx + 20].bloco = "@";
        idx = idx + 20;
        ValidacaoMovimento = true; 
        return;
    }

    do{
        if(BlocoEspecial == "✚" || BlocoEspecial == "⛏"){
            cout << "\n Deseja coletar o item? \n";
            cout << "1 - Sim";
            cout << "2 - Não";
            cin >> escolha;

            if(escolha == 1){

                if(BlocoEspecial == "✚"){
                    Item novo = CriarPocao();
                    AdicionarItem(player, novo);
                    cout << "\nPoção de cura adicionado ao inventário!\n";
                    ValidacaoMovimento = true;
                    BlocoEspecial = "nulo";
                    return;
                } else {
                    Item novo = CriarBroca();
                    AdicionarItem(player, novo);
                    cout << "\nBroca adicionada ao inventário!\n";
                    ValidacaoMovimento = true;
                    BlocoEspecial = "nulo";
                    return;
                }
            }
            if(escolha == 2){
                ValidacaoMovimento = true;
                return;
            }
            if(escolha < 1 || escolha > 2){
                cout << "\nOpção inválida, tente novamente!\n";
            }
        } 
    } while(escolha < 1 || escolha > 2); 
}