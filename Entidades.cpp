#include "head.h"
#include <iostream>
#include <limits>
using namespace std; 

string BlocoEspecial = "nulo";
const int largura = 20;

void MovimentoJogador(std::vector<Mapa> &mapas, struct Jogador &player, vector<Item> &inventario, bool &ConcluiuMapa, int &qtde){
    bool ValidacaoMovimento = false, quebrou = false;; 
    char movimento;
    int idx = -1, escolha = 0;

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
            AndarDireita(mapas, player, idx, BlocoEspecial, ValidacaoMovimento, movimento, ConcluiuMapa);
        } else if (movimento == 'a' || movimento == 'A'){
            AndarEsquerda(mapas, player, idx, BlocoEspecial, movimento, ValidacaoMovimento);
        } else if (movimento == 'w' || movimento == 'W'){
            AndarCima (mapas, player, idx, BlocoEspecial, movimento, ValidacaoMovimento);
        } else if (movimento == 's' || movimento == 'S'){
            AndarBaixo(mapas, player, idx, BlocoEspecial, movimento, ValidacaoMovimento, ConcluiuMapa);
        } else if (movimento == 'c' || movimento == 'C'){
            AbrirInventario(player, inventario, ValidacaoMovimento, mapas); 
        } else if (movimento == 'l' || movimento == 'L'){
            QuebrarParede(player, inventario, mapas, movimento);
        }

        if (movimento == 'l' || movimento == 'L'){
            quebrou = QuebrarParede(player, inventario, mapas, movimento);
            ValidacaoMovimento = quebrou;
        }

        MovimentoMonstro(mapas, qtde);
        

    } while (!ValidacaoMovimento);
    return;
}

void AbrirInventario(Jogador &player, std::vector<Item> &inventario, bool &ValidacaoMovimento, std::vector<Mapa> &mapas){
    char input;

    do{
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
        if(player.dinheiro < 9){
            cout << " |R$:" << player.dinheiro << "                  |\n";
        } else if(player.dinheiro >= 10 && player.dinheiro <= 99) {
            cout << " |R$:" << player.dinheiro << "                 |\n";
        } else if(player.dinheiro > 99 && player.dinheiro <= 999){
            cout << " |R$:" << player.dinheiro << "                |\n";
        } else {
            cout << " |R$:" << player.dinheiro << "               |\n";
        }
        cout << " └──────────────────────┘\n";

        cout << "\n[F] - Largar item\n";
        cout << "[Q] - Fechar inventario\n";
        cin >> input;

        if(input == 'F' || input == 'f'){
            LargarItem(player, inventario, mapas);
        }

    } while(input != 'q' && input != 'Q');

    ValidacaoMovimento = true;
    return;
}

bool AdicionarItem(Jogador &player, const Item &novo){
    int count = 0;

    for(int i = 0; i < 3; i++){
        if (player.inventario[i].nome == ""){
            player.inventario[i] = novo;
            return true;
        }
    }
    return false;
}


void LargarItem(Jogador &player, std::vector<Item> &inventario, std::vector<Mapa> &mapas){
     int escolha;

    cout << "Escolha qual item deseja largar (1 a 3):\n";
    cin >> escolha;

    if (escolha < 1 || escolha > 3){
        cout << "Slot inválido!\n";
        return;
    }

    int idxSlot = escolha - 1;

    if (player.inventario[idxSlot].nome == ""){
        cout << "Esse slot já está vazio!\n";
        return;
    }

    if (BlocoEspecial != "nulo"){
        cout << "Já tem um item no chão nessa posição. Pegue/ande antes de largar outro.\n";
        return;
    }

    BlocoEspecial = player.inventario[idxSlot].img;

    player.inventario[idxSlot].nome = "";
    player.inventario[idxSlot].img = "";

    ReorganizarItens(player);
}
//;

void ReorganizarItens(Jogador &player){
    vector<Item> novo(3);
    int k = 0;

    for(int i = 0; i < 3; i++){
        if(player.inventario[i].nome != ""){
            novo[k++] = player.inventario[i];
        }
    }

    player.inventario = novo;
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

bool QuebrarParede(struct Jogador &player, std::vector<Item> &inventario, std::vector<Mapa> & mapas, char &movimento){
    bool validacao = false;
    int escolha;

    for(int i = 0; i < 3; i++){
        
        if(player.inventario[i].nome == "Broca"){
            cout << "Você possui uma broca, deseja quebrar a parede? 1 - sim, 2 - não";     

        while (!(cin >> escolha)) {
            cin.clear(); // limpa o estado de erro
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // joga fora a linha ruim
            cout << "Entrada inválida. Digite um número: ";
        }

            if(escolha == 2){
                return false;
            } else if(escolha < 1 || escolha > 2){
                cout << "\nOpção inválida!\n";
                return false;
            } else if(escolha == 1){
                cout << "\nQuebrando...\n";
                Sleep(100);

                player.inventario[i].nome = "";
                player.inventario[i].img = "";

                for(int j = 0; j < mapas.size(); j++){
                    if(mapas[j].bloco == "@"){
                        if(movimento == 'D' || movimento == 'd'){
                            mapas[j + 1].bloco = ".";
                            return true; 
                        } else if(movimento == 's' || movimento == 'S'){
                            mapas[j + 20].bloco = ".";
                            return true;
                        } else if(movimento == 'a' || movimento == 'A'){
                            mapas[j - 1].bloco = ".";
                            return true;
                        } else {
                            mapas[j - 20].bloco = ".";
                            return true;
                        }
                    }
                }
            } else {
                cout << "\nOpção inválida!\n";
                return false;
            }
        }
    }
    return false;
}



//funcoes de movimentação
void AndarDireita(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento, char &movimento, bool &ConcluiuMapa){ 
    int escolha = 0;
    vector<Item> inventario;

    if (idx == -1) {
        cout << "\nBUG: não achei o jogador '@' no mapa!\n";
        ValidacaoMovimento = true;
        return;
    }
        
    if(idx % largura == largura - 1){
        cout << "Movimento inválido, tente novamente!\n";
        ValidacaoMovimento = true;
        return;
    }

    if(mapas[idx + 1].bloco == "|"){
        if(QuebrarParede(player, inventario, mapas, movimento) == true){
            ValidacaoMovimento = true;
            return;
        }

        ValidacaoMovimento = false;
        cout << "\nMovimento inválido, tente novamente! \n";
        return;

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
        ValidacaoMovimento = true; 
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

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nPoção de cura adicionado ao inventário!\n";
                        ValidacaoMovimento = true;
                        BlocoEspecial = "nulo";
                        return;
                    }
                } else {
                    Item novo = CriarBroca();

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nBroca adicionada ao inventário!\n";
                        ValidacaoMovimento = true;
                        BlocoEspecial = "nulo";
                        return;
                    }
                }
            } else if(escolha == 2){
                ValidacaoMovimento = true;
                return;
            } else {
                cout << "\nOpção inválida, tente novamente!\n";
            }
        } 

    } while(escolha < 1 && escolha > 2);

}

void AndarEsquerda(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, char &movimento, bool &ValidacaoMovimento){
    bool ConcluiuMapa = false; 
    int escolha = 0;
    vector<Item> inventario;

    if (idx == -1) {
        cout << "\nBUG: não achei o jogador '@' no mapa!\n";
        ValidacaoMovimento = true;
        return;
    }

    if(idx % largura == 0){
        cout << "Movimento inválido, tente novamente!\n";
        ValidacaoMovimento = true;
        return;
    }

    if(mapas[idx - 1].bloco == "|"){
        if(QuebrarParede(player, inventario, mapas, movimento) == true){
            ValidacaoMovimento = true;
            return;
        }

        ValidacaoMovimento = false;
        cout << "\nMovimento inválido, tente novamente! \n";
        return;

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
        ValidacaoMovimento = true; 
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

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nPoção de cura adicionado ao inventário!\n";
                        ValidacaoMovimento = true;
                        BlocoEspecial = "nulo";
                        return;
                    }
                } else {
                    Item novo = CriarBroca();

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nBroca adicionada ao inventário!\n";
                        ValidacaoMovimento = true;
                        BlocoEspecial = "nulo";
                        return;
                    }
                }
            }

        } else if(escolha == 2){
            ValidacaoMovimento = true;
            return;
        } else {
            cout << "\nOpção inválida, tente novamente!\n";
        }

    } while(escolha < 1 && escolha > 2);
}

void AndarCima(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, char &movimento, bool &ValidacaoMovimento){
    bool ConcluiuMapa = false; 
    int escolha = 0;
    vector<Item> inventario;

    if (idx == -1) {
        cout << "\nBUG: não achei o jogador '@' no mapa!\n";
        ValidacaoMovimento = true;
        return;
    }

    if(idx < largura){
        cout << "Movimento inválido, tente novamente!\n";
        ValidacaoMovimento = true;
        return;
    }

    if(mapas[idx - 20].bloco == "|"){
        if(QuebrarParede(player, inventario, mapas, movimento) == true){
            ValidacaoMovimento = true;
            return;
        }

        ValidacaoMovimento = false;
        cout << "\nMovimento inválido, tente novamente! \n";
        return;

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
                idx = idx - 20;
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
        ValidacaoMovimento = true; 
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

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nPoção de cura adicionado ao inventário!\n";
                        ValidacaoMovimento = true;
                        BlocoEspecial = "nulo";
                        return;
                    }
                } else {
                    Item novo = CriarBroca();

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nBroca adicionada ao inventário!\n";
                        ValidacaoMovimento = true;
                        BlocoEspecial = "nulo";
                        return;
                    }
                }
            }
        } else if(escolha == 2){
            ValidacaoMovimento = true;
            return;
        } else {
            cout << "\nOpção inválida, tente novamente!\n";
        }

    } while(escolha < 1 && escolha > 2);
}

void AndarBaixo(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, char &movimento, bool &ValidacaoMovimento, bool &ConcluiuMapa){ 
    int escolha = 0;
    vector<Item> inventario;

    if (idx == -1) {
        cout << "\nBUG: não achei o jogador '@' no mapa!\n";
        ValidacaoMovimento = true;
        return;
    }

    if(idx + largura >= mapas.size()){
        cout << "Movimento inválido, tente novamente!\n";
        ValidacaoMovimento = true;
        return;

     } else if(mapas[idx + 20].bloco == "|" ){
        if(QuebrarParede(player, inventario, mapas, movimento) == true){
            ValidacaoMovimento = true;
            return;
        }

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
        ValidacaoMovimento = true; 
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

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nPoção de cura adicionado ao inventário!\n";
                        ValidacaoMovimento = true;
                        BlocoEspecial = "nulo";
                        return;
                    }
                    
                } else {
                    Item novo = CriarBroca();

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nBroca adicionada ao inventário!\n";
                        ValidacaoMovimento = true;
                        BlocoEspecial = "nulo";
                        return;
                    }
                }
            }
        } else if(escolha == 2){
            ValidacaoMovimento = true;
            return;
        } else {
            cout << "\nOpção inválida, tente novamente!\n";
        }

    } while(escolha < 1 && escolha > 2);
}

void MovimentoMonstro(std::vector<Mapa> &mapas, int &qtde){
    int count = 0, m = 0;
    bool ValidacaoDirecao = false;

    for(int i = 0; i < mapas.size(); i++){
        if(mapas[i].bloco == "8"){
            int direcao = 0;

//Nota direções: 0 = D - sub E // 1 = A - sub Q // 2 = W - Z // 3 = S - sub C;

            do{
                direcao = rand() % 3;

                if(direcao = 0){

                    if(mapas[i + 1].bloco != "."){
                        if(mapas[i - 19].bloco != "." || i - 19 < mapas.size()){
                            ValidacaoDirecao = false;
                        } else {
                            mapas[i].bloco = ".";
                            mapas[i - 19].bloco = "8";
                            ValidacaoDirecao = true;
                        }
                    } else {
                        mapas[i].bloco = ".";
                        mapas[i + 1].bloco = "8";
                        ValidacaoDirecao = true;
                    }

                } else if(direcao = 1){
                    
                    if(mapas[i - 1].bloco != "."){
                        if(mapas[i - 21].bloco != "." || i - 21 < mapas.size()){
                            ValidacaoDirecao = false;
                        } else{
                            mapas[i].bloco = ".";
                            mapas[i - 21].bloco = "8";
                            ValidacaoDirecao = true; 
                        }
                    } else {
                        mapas[i].bloco = ".";
                        mapas[i - 1].bloco = "8";
                        ValidacaoDirecao = true; 
                    }

                } else if(direcao = 2){

                    if(mapas[i - 20].bloco != "."){
                        if(mapas[i + 19].bloco != "." || i + 19 < mapas.size()){
                            ValidacaoDirecao = false;
                        } else{
                            mapas[i].bloco = ".";
                            mapas[i + 19].bloco = "8";
                            ValidacaoDirecao = true; 
                        }
                    } else {
                        mapas[i].bloco = ".";
                        mapas[i - 20].bloco = "8";
                        ValidacaoDirecao = true; 
                    }

                } else {

                    if(mapas[i + 20].bloco != "."){
                        if(mapas[i + 21].bloco != "." || i + 21 < mapas.size()){
                            ValidacaoDirecao = false;
                        } else{
                            mapas[i].bloco = ".";
                            mapas[i + 21].bloco = "8";
                            ValidacaoDirecao = true; 
                        }
                    } else {
                        mapas[i].bloco = ".";
                        mapas[i + 20].bloco = "8";
                        ValidacaoDirecao = true; 
                    }

                }

            } while(ValidacaoDirecao == false);
        }     
    }
    return;
}