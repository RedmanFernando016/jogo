#include "head.h"
#include <iostream>
#include <limits>
using namespace std; 

string BlocoEspecial = "nulo";
const int largura = 20;

void MovimentoJogador(std::vector<Mapa> &mapas, struct Jogador &player, vector<Item> &inventario, bool &ConcluiuMapa, int &qtde, std::vector<MapaCombate> &mapacombate, struct Monstro &oponente, bool &derrota){
    bool ValidacaoMovimento = false, quebrou = false;; 
    char movimento;
    int idx = -1, escolha = 0;

    do{    
        cout << "\nDigite o movimento: \n";
        cin >> movimento;

        for(int i = 0; i < mapas.size(); i++){
            if(mapas[i].bloco == "@"){
                idx = i;
                break;
            }
        }

        if(movimento == 'd' || movimento == 'D'){
            AndarDireita(mapas, player, idx, BlocoEspecial, ValidacaoMovimento, movimento, ConcluiuMapa, mapacombate, oponente, derrota);
        } else if (movimento == 'a' || movimento == 'A'){
            AndarEsquerda(mapas, player, idx, BlocoEspecial, movimento, ValidacaoMovimento, mapacombate, oponente, derrota);
        } else if (movimento == 'w' || movimento == 'W'){
            AndarCima (mapas, player, idx, BlocoEspecial, movimento, ValidacaoMovimento, mapacombate, oponente, derrota);
        } else if (movimento == 's' || movimento == 'S'){
            AndarBaixo(mapas, player, idx, BlocoEspecial, movimento, ValidacaoMovimento, ConcluiuMapa, mapacombate, oponente, derrota);
        } else if (movimento == 'c' || movimento == 'C'){
            AbrirInventario(player, inventario, ValidacaoMovimento, mapas); 
        }

        if(derrota == true){
            cout << "\nVocê morreu!\n";
            Sleep(3000);
            abort();
        }

        MovimentoMonstro(mapas, qtde, mapacombate, oponente, derrota, player, ValidacaoMovimento);
        

    } while (!ValidacaoMovimento);
    return;
}

void AbrirInventario(Jogador &player, std::vector<Item> &inventario, bool &ValidacaoMovimento, std::vector<Mapa> &mapas){
    char input;
    int margem = 18;

    do{
        system("cls");

        cout << "\n";
        cout << string(margem, ' ') << "╔══════════════════════════════╗\n";
        cout << string(margem, ' ') << "║         INVENTÁRIO           ║\n";
        cout << string(margem, ' ') << "╠══════════════════════════════╣\n";
        cout << string(margem, ' ') << "║ Itens:                       ║\n";
        cout << string(margem, ' ') << "║                              ║\n";

        for(int i = 0; i < 3; i++){
            if(player.inventario[i].img == "⛏"){
                cout << string(margem, ' ') << "║ [" << player.inventario[i].img << "] - Picareta               ║\n";
            } else if(player.inventario[i].img == "✚"){
                cout << string(margem, ' ') << "║ [" << player.inventario[i].img << "] - Poção de cura          ║\n";
            } else {
                cout << string(margem, ' ') << "║ [ ] - ...                    ║\n";
            }
        }

        cout << string(margem, ' ') << "║                              ║\n";

        if(player.dinheiro < 10){
            cout << string(margem, ' ') << "║ R$: " << player.dinheiro << "                        ║\n";
        } else if(player.dinheiro <= 99){
            cout << string(margem, ' ') << "║ R$: " << player.dinheiro << "                       ║\n";
        } else if(player.dinheiro <= 999){
            cout << string(margem, ' ') << "║ R$: " << player.dinheiro << "                      ║\n";
        } else {
            cout << string(margem, ' ') << "║ R$: " << player.dinheiro << "                     ║\n";
        }

        if(player.vida < 10){
            cout << string(margem, ' ') << "║ HP: " << player.vida << "                        ║\n";
        } else if(player.vida <= 99){
            cout << string(margem, ' ') << "║ HP: " << player.vida << "                       ║\n";
        } else {
            cout << string(margem, ' ') << "║ HP: " << player.vida << "                      ║\n";
        }

        if(player.estamina < 10){
            cout << string(margem, ' ') << "║ STA: " << player.estamina << "                       ║\n";
        } else if(player.estamina <= 99){
            cout << string(margem, ' ') << "║ STA: " << player.estamina << "                      ║\n";
        } else {
            cout << string(margem, ' ') << "║ STA: " << player.estamina << "                     ║\n";
        }

        cout << string(margem, ' ') << "╠══════════════════════════════╣\n";
        cout << string(margem, ' ') << "║ [F] - Largar item            ║\n";
        cout << string(margem, ' ') << "║ [P] - Utilizar Cura          ║\n";
        cout << string(margem, ' ') << "║ [Q] - Fechar inventário      ║\n";
        cout << string(margem, ' ') << "╚══════════════════════════════╝\n\n";

        cout << string(margem, ' ') << "Escolha: \n";
        cin >> input;

        if(input == 'F' || input == 'f'){
            LargarItem(player, inventario, mapas);
        }

        if(input == 'P' || input =='p'){
            Cura(player);
        }

    } while(input != 'q' && input != 'Q');

    ValidacaoMovimento = true;
    return;
}

void Cura(Jogador &player){
    bool TemCura = false;
    int idx;

    for(int i = 0; i < 3; i++){
        if(player.inventario[i].img == "✚"){
            if(TemCura = true);
            idx = i;
            break;
        }
    }
    if(TemCura == true){
        if(player.vida == 100){
            cout << "\nVida já está cheia!\n";
            Sleep(1000);
            return;
        }

        player.inventario[idx].img = "";
        player.inventario[idx].nome = "";
        ReorganizarItens(player);

        player.vida += 80;
        if(player.vida > 100){
            player.vida = 100;
        }
        return;
    }

    if(TemCura == false){
        cout << "\nSem cura para utilizar!\n";
        Sleep(1000);
        return;
    }
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
        Sleep(1000);
        return;
    }

    int idxSlot = escolha - 1;

    if (player.inventario[idxSlot].nome == ""){
        cout << "Esse slot já está vazio!\n";
        Sleep(1000);
        return;
    }

    if (BlocoEspecial != "nulo"){
        cout << "Já tem um item no chão nessa posição. Pegue/ande antes de largar outro.\n";
        Sleep(2000);
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
            cout << "Você possui uma broca, deseja quebrar a parede? 1 - sim, 2 - não\n";     

        while (!(cin >> escolha)) {
            cin.clear(); // limpa o estado de erro
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // joga fora a linha ruim
            cout << "Entrada inválida. Digite um número: \n";
        }

            if(escolha == 2){
                return false;
            } else if(escolha < 1 || escolha > 2){
                cout << "\nOpção inválida!\n";
                return false;
            } else if(escolha == 1){
                cout << "\nQuebrando...\n";
                Sleep(1000);

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
                Sleep(1000);
                return false;
            }
        }
    }
    return false;
}



//funcoes de movimentação
void AndarDireita(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, bool &ValidacaoMovimento, char &movimento, bool &ConcluiuMapa, std::vector<MapaCombate> &mapacombate, struct Monstro &oponente, bool &derrota){ 
    int escolha = 0;
    vector<Item> inventario;

    if (idx == -1) {
        cout << "\nBUG: não achei o jogador '@' no mapa!\n";
        ValidacaoMovimento = true;
        return;
    }
        
    if(idx % largura == largura - 1){
        cout << "Movimento inválido, tente novamente!\n";
        Sleep(1000);
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
        Sleep(1000);
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

    } else if (mapas[idx + 1].bloco == "8"){
        if(Combate(mapacombate, player, oponente) == true){
            ValidacaoMovimento = true;
            mapas[idx + 1].bloco = "@";
            mapas[idx].bloco = ".";
            idx = idx + 1;
            return;
        } else {
            ValidacaoMovimento = true;
            derrota = true;
            return;
        }

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
            cout << "2 - Não\n";

            while (!(cin >> escolha)) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\nEntrada inválida. Digite um número: \n";
                Sleep(1000);
            }

            if(escolha == 1){
                if(BlocoEspecial == "✚"){
                    Item novo = CriarPocao();

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        Sleep(1000);
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nPoção de cura adicionado ao inventário!\n";
                        Sleep(1000);
                        ValidacaoMovimento = true;
                        BlocoEspecial = "nulo";
                        return;
                    }
                } else {
                    Item novo = CriarBroca();

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        Sleep(1000);
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nBroca adicionada ao inventário!\n";
                        Sleep(1000);
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
                Sleep(1000);
            }
        } 

    } while(escolha < 1 && escolha > 2);

}

void AndarEsquerda(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, char &movimento, bool &ValidacaoMovimento, std::vector<MapaCombate> &mapacombate, struct Monstro &oponente, bool &derrota){
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
        Sleep(1000);
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

    } else if (mapas[idx - 1].bloco == "8"){
        if(Combate(mapacombate, player, oponente) == true){
            ValidacaoMovimento = true;
            mapas[idx - 1].bloco = "@";
            mapas[idx].bloco = ".";
            idx = idx - 1;
            return;
        } else {
            ValidacaoMovimento = true;
            derrota = true;
            return;
        }

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
            cout << "2 - Não\n";
            while (!(cin >> escolha)) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\nEntrada inválida. Digite um número: \n";
                Sleep(1000);
            }

            if(escolha == 1){
                if(BlocoEspecial == "✚"){
                    Item novo = CriarPocao();

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        Sleep(1000);
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nPoção de cura adicionado ao inventário!\n";
                        Sleep(1000);
                        ValidacaoMovimento = true;
                        BlocoEspecial = "nulo";
                        return;
                    }

                } else {
                    Item novo = CriarBroca();

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        Sleep(1000);
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nBroca adicionada ao inventário!\n";
                        Sleep(1000);
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
            Sleep(1000);
            }    
        }    
    } while(escolha < 1 && escolha > 2);
}

void AndarCima(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, char &movimento, bool &ValidacaoMovimento, std::vector<MapaCombate> &mapacombate, struct Monstro &oponente, bool &derrota){
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
        Sleep(1000);
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
        Sleep(1000);
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

    } else if (mapas[idx - 20].bloco == "8"){
        if(Combate(mapacombate, player, oponente) == true){
            ValidacaoMovimento = true;
            mapas[idx - 20].bloco = "@";
            mapas[idx].bloco = ".";
            idx = idx - 20;
            return;
        } else {
            ValidacaoMovimento = true;
            derrota = true;
            return;
        }

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
            cout << "2 - Não\n";
            while (!(cin >> escolha)) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\nEntrada inválida. Digite um número: \n";
                Sleep(1000);
            }

            if(escolha == 1){
                if(BlocoEspecial == "✚"){
                    Item novo = CriarPocao();

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        Sleep(1000);
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nPoção de cura adicionado ao inventário!\n";
                        Sleep(1000);
                        ValidacaoMovimento = true;
                        BlocoEspecial = "nulo";
                        return;
                    }
                } else {
                    Item novo = CriarBroca();

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        Sleep(1000);
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nBroca adicionada ao inventário!\n";
                        Sleep(1000);
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
                Sleep(1000);
            }
        }
    } while(escolha < 1 && escolha > 2);
}

void AndarBaixo(std::vector<Mapa> &mapas, struct Jogador &player, int &idx, std::string &BlocoEspecial, char &movimento, bool &ValidacaoMovimento, bool &ConcluiuMapa, std::vector<MapaCombate> &mapacombate, struct Monstro &oponente, bool &derrota){ 
    int escolha = 0;
    vector<Item> inventario;

    if (idx == -1) {
        cout << "\nBUG: não achei o jogador '@' no mapa!\n";
        ValidacaoMovimento = true;
        return;
    }

    if(idx + largura >= mapas.size()){
        cout << "Movimento inválido, tente novamente!\n";
        Sleep(1000);
        ValidacaoMovimento = true;
        return;

     } else if(mapas[idx + 20].bloco == "|" ){
        if(QuebrarParede(player, inventario, mapas, movimento) == true){
            ValidacaoMovimento = true;
            return;
        }

        ValidacaoMovimento = false;
        cout << "\nMovimento inválido, tente novamente! \n";
        Sleep(1000);
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

    } else if (mapas[idx + 20].bloco == "8"){
        if(Combate(mapacombate, player, oponente) == true){
            ValidacaoMovimento = true;
            mapas[idx + 20].bloco = "@";
            mapas[idx].bloco = ".";
            idx = idx + 20;
            return;
        } else {
            ValidacaoMovimento = true;
            derrota = true;
            return;
        }

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
            cout << "2 - Não\n";
            while (!(cin >> escolha)) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\nEntrada inválida. Digite um número: \n";
                Sleep(1000);
            }

            if(escolha == 1){
                if(BlocoEspecial == "✚"){
                    Item novo = CriarPocao();

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        Sleep(1000);
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nPoção de cura adicionado ao inventário!\n";
                        Sleep(1000);
                        ValidacaoMovimento = true;
                        BlocoEspecial = "nulo";
                        return;
                    }
                    
                } else {
                    Item novo = CriarBroca();

                    if(AdicionarItem(player, novo) == false){
                        cout << "inventário cheio!";
                        Sleep(1000);
                        ValidacaoMovimento = false;
                        return;
                    } else {
                        cout << "\nBroca adicionada ao inventário!\n";
                        Sleep(1000);
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
                Sleep(1000);
            }
        }
    } while(escolha < 1 && escolha > 2);
}

void MovimentoMonstro(std::vector<Mapa> &mapas, int &qtdestd, std::vector<MapaCombate> &mapacombate, struct Monstro &oponente, bool &derrota, struct Jogador &player, bool &ValidacaoMovimento){
    vector<int> PosMonstro;

    for(int i = 0; i < mapas.size(); i++){
        if(mapas[i].bloco == "8"){
            PosMonstro.push_back(i);
        }
    }

    for(int k = 0; k < PosMonstro.size(); k++){
        int i = PosMonstro[k];

        if(mapas[i].bloco != "8"){
            continue;
        }

        int tent = 0;
        bool ValidacaoDirecao = false;

        do{
            int direcao = rand() % 4;

            // 0 = direita | diagonal: cima-direita (-19)
            if(direcao == 0){

                if(i % largura != largura - 1 && i + 1 < mapas.size()){
                    if(mapas[i + 1].bloco == "@"){
                        if(Combate(mapacombate, player, oponente) == true){
                            ValidacaoDirecao = true;
                            mapas[i].bloco = ".";
                        } else {
                            ValidacaoDirecao = true;
                            derrota = true;
                        }
                    } else if(mapas[i + 1].bloco == "."){
                        mapas[i].bloco = ".";
                        mapas[i + 1].bloco = "8";
                        ValidacaoDirecao = true;
                    } else if(i >= largura && i - 19 >= 0){
                        if(mapas[i - 19].bloco == "@"){
                            if(Combate(mapacombate, player, oponente) == true){
                                ValidacaoDirecao = true;
                                mapas[i].bloco = ".";
                            } else {
                                ValidacaoDirecao = true;
                                derrota = true;
                            }
                        } else if(mapas[i - 19].bloco == "."){
                            mapas[i].bloco = ".";
                            mapas[i - 19].bloco = "8";
                            ValidacaoDirecao = true;
                        } else {
                            tent++;
                        }
                    } else {
                        tent++;
                    }
                } else if(i >= largura && i % largura != largura - 1 && i - 19 >= 0){
                    if(mapas[i - 19].bloco == "@"){
                        if(Combate(mapacombate, player, oponente) == true){
                            ValidacaoDirecao = true;
                            mapas[i].bloco = ".";
                        } else {
                            ValidacaoDirecao = true;
                            derrota = true;
                        }
                    } else if(mapas[i - 19].bloco == "."){
                        mapas[i].bloco = ".";
                        mapas[i - 19].bloco = "8";
                        ValidacaoDirecao = true;
                    } else {
                        tent++;
                    }
                } else {
                    tent++;
                }
            }

            // 1 = esquerda | diagonal: cima-esquerda (-21)
            else if(direcao == 1){

                if(i % largura != 0 && i - 1 >= 0){
                    if(mapas[i - 1].bloco == "@"){
                        if(Combate(mapacombate, player, oponente) == true){
                            ValidacaoDirecao = true;
                            mapas[i].bloco = ".";
                        } else {
                            ValidacaoDirecao = true;
                            derrota = true;
                        }
                    } else if(mapas[i - 1].bloco == "."){
                        mapas[i].bloco = ".";
                        mapas[i - 1].bloco = "8";
                        ValidacaoDirecao = true;
                    } else if(i >= largura && i - 21 >= 0){
                        if(mapas[i - 21].bloco == "@"){
                            if(Combate(mapacombate, player, oponente) == true){
                                ValidacaoDirecao = true;
                                mapas[i].bloco = ".";
                            } else {
                                ValidacaoDirecao = true;
                                derrota = true;
                            }
                        } else if(mapas[i - 21].bloco == "."){
                            mapas[i].bloco = ".";
                            mapas[i - 21].bloco = "8";
                            ValidacaoDirecao = true;
                        } else {
                            tent++;
                        }
                    } else {
                        tent++;
                    }
                } else {
                    tent++;
                }
            }

            // 2 = cima | diagonal: cima-direita (-19)
            else if(direcao == 2){

                if(i >= largura && i - 20 >= 0){
                    if(mapas[i - 20].bloco == "@"){
                        if(Combate(mapacombate, player, oponente) == true){
                            ValidacaoDirecao = true;
                            mapas[i].bloco = ".";
                        } else {
                            ValidacaoDirecao = true;
                            derrota = true;
                        }
                    } else if(mapas[i - 20].bloco == "."){
                        mapas[i].bloco = ".";
                        mapas[i - 20].bloco = "8";
                        ValidacaoDirecao = true;
                    } else if(i % largura != largura - 1 && i - 19 >= 0){
                        if(mapas[i - 19].bloco == "@"){
                            if(Combate(mapacombate, player, oponente) == true){
                                ValidacaoDirecao = true;
                                mapas[i].bloco = ".";
                            } else {
                                ValidacaoDirecao = true;
                                derrota = true;
                            }
                        } else if(mapas[i - 19].bloco == "."){
                            mapas[i].bloco = ".";
                            mapas[i - 19].bloco = "8";
                            ValidacaoDirecao = true;
                        } else {
                            tent++;
                        }
                    } else {
                        tent++;
                    }
                } else {
                    tent++;
                }
            }

            // 3 = baixo | diagonal: baixo-direita (+21)
            else{

                if(i + largura < mapas.size() && i + 20 < mapas.size()){
                    if(mapas[i + 20].bloco == "@"){
                        if(Combate(mapacombate, player, oponente) == true){
                            ValidacaoDirecao = true;
                            mapas[i].bloco = ".";
                        } else {
                            ValidacaoDirecao = true;
                            derrota = true;
                        }
                    } else if(mapas[i + 20].bloco == "."){
                        mapas[i].bloco = ".";
                        mapas[i + 20].bloco = "8";
                        ValidacaoDirecao = true;
                    } else if(i % largura != largura - 1 && i + 21 < mapas.size()){
                        if(mapas[i + 21].bloco == "@"){
                            if(Combate(mapacombate, player, oponente) == true){
                                ValidacaoDirecao = true;
                                mapas[i].bloco = ".";
                            } else {
                                ValidacaoDirecao = true;
                                derrota = true;
                            }
                        } else if(mapas[i + 21].bloco == "."){
                            mapas[i].bloco = ".";
                            mapas[i + 21].bloco = "8";
                            ValidacaoDirecao = true;
                        } else {
                            tent++;
                        }
                    } else {
                        tent++;
                    }
                } else {
                    tent++;
                }
            }

        } while(ValidacaoDirecao == false && tent < 50);
    }
}
