#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

struct Territorio {
    char nome[20];
    int exercitos;
    int dono; // 1 para Humano, 2 para IA
};

void exibirMapa(Territorio* mapa, int total) {
    std::cout << "\n--- ESTADO DO MAPA ---\n";
    for (int i = 0; i < total; i++) {
        std::cout << i << ". [" << (mapa[i].dono == 1 ? "JOGADOR" : "IA") << "] " 
                  << mapa[i].nome << ": " << mapa[i].exercitos << " exercitos\n";
    }
}

int main() {
    srand(time(0));
    int numTerritorios = 5;

    // Alocação Dinâmica com malloc
    Territorio* mapa = (Territorio*)malloc(numTerritorios * sizeof(Territorio));
    if (!mapa) return 1;

    // Inicialização
    const char* nomes[] = {"Brasil", "Angola", "Franca", "Japao", "Mexico"};
    for (int i = 0; i < numTerritorios; i++) {
        sprintf(mapa[i].nome, "%s", nomes[i]);
        mapa[i].exercitos = rand() % 5 + 2;
        mapa[i].dono = (i < 3) ? 1 : 2; // Jogador começa com 3, IA com 2
    }

    bool jogoAtivo = true;
    int turno = 1;

    while (jogoAtivo) {
        int atacanteID = (turno % 2 != 0) ? 1 : 2;
        std::cout << "\n========================";
        std::cout << "\nTURNO " << turno << " - " << (atacanteID == 1 ? "SUA VEZ" : "VEZ DA IA");
        exibirMapa(mapa, numTerritorios);

        int de, para;
        if (atacanteID == 1) {
            std::cout << "\nEscolha o ID do seu territorio para atacar e o alvo (ex: 0 4): ";
            std::cin >> de >> para;
        } else {
            de = 3 + (rand() % 2); // IA escolhe entre seus territórios iniciais simplificadamente
            para = rand() % 3;
            std::cout << "\nIA decidiu atacar de " << de << " para " << para << "\n";
        }

        // Validação básica
        if (mapa[de].dono == atacanteID && mapa[para].dono != atacanteID && mapa[de].exercitos > 1) {
            int dadoAtaque = rand() % 6 + 1;
            int dadoDefesa = rand() % 6 + 1;

            std::cout << "Dados -> Atacante: " << dadoAtaque << " | Defesa: " << dadoDefesa << "\n";

            if (dadoAtaque > dadoDefesa) {
                std::cout << "Vitoria no ataque!\n";
                mapa[para].exercitos--;
                if (mapa[para].exercitos <= 0) {
                    std::cout << "TERRITORIO CONQUISTADO!\n";
                    mapa[para].dono = atacanteID;
                    mapa[para].exercitos = 1;
                    mapa[de].exercitos--;
                }
            } else {
                std::cout << "Defesa resistiu!\n";
                mapa[de].exercitos--;
            }
        } else {
            std::cout << "Movimento invalido ou exercitos insuficientes!\n";
        }

        // Checar vitória
        int contJogador = 0;
        for(int i=0; i<numTerritorios; i++) if(mapa[i].dono == 1) contJogador++;
        if(contJogador == 0 || contJogador == numTerritorios) {
            std::cout << "\nFIM DE JOGO! Vencedor: " << (contJogador == 5 ? "Jogador" : "IA") << "\n";
            jogoAtivo = false;
        }

        turno++;
        if(turno > 20) jogoAtivo = false; // Limite de turnos para segurança
    }

    // Liberação de memória obrigatória
    free(mapa);
    std::cout << "Memoria desalocada com sucesso.\n";
    return 0;
}