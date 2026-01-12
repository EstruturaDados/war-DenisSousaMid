#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

// Estrutura para os Territórios
struct Territorio {
    std::string nome;
    int tropas;
    int dono; // 1 para Jogador, 2 para Computador
};

// Estrutura para Missões
struct Missao {
    int id;
    std::string descricao;
    int metaTerritorios;
};

// Função para exibir o estado atual do tabuleiro
void exibirTabuleiro(Territorio* mapa, int n) {
    std::cout << "\n========= TABULEIRO ATUAL (2026) =========\n";
    for (int i = 0; i < n; i++) {
        std::cout << i << ". [" << (mapa[i].dono == 1 ? "VOCE" : "IA  ") << "] " 
                  << mapa[i].nome << " - Tropas: " << mapa[i].tropas << "\n";
    }
    std::cout << "==========================================\n";
}

int main() {
    srand(time(0));
    const int totalTerritorios = 5;

    // 1. Alocação Dinâmica com malloc (Gerenciamento manual de memória)
    Territorio* mapa = (Territorio*)malloc(totalTerritorios * sizeof(Territorio));
    if (mapa == NULL) return 1;

    // Inicialização dos territórios
    std::string nomes[] = {"Brasil", "Egito", "Rússia", "Japão", "Canadá"};
    for (int i = 0; i < totalTerritorios; i++) {
        mapa[i].nome = nomes[i];
        mapa[i].tropas = (rand() % 4) + 2; // Começa com 2 a 5 tropas
        mapa[i].dono = (i < 3) ? 1 : 2;    // Jogador começa com 3, IA com 2
    }

    // 2. Missões Estratégicas
    Missao missaoJogador = {1, "Conquistar 4 territórios", 4};
    std::cout << "SUA MISSAO: " << missaoJogador.descricao << "\n";

    bool jogoAtivo = true;
    int turno = 1;

    // 3. Loop de Turnos
    while (jogoAtivo) {
        int atacanteAtual = (turno % 2 != 0) ? 1 : 2;
        exibirTabuleiro(mapa, totalTerritorios);
        
        std::cout << "\nTURNO " << turno << " - " << (atacanteAtual == 1 ? "SUA VEZ" : "VEZ DA IA") << "\n";

        int de, para;
        if (atacanteAtual == 1) {
            std::cout << "Escolha o ID da sua origem e o ID do alvo (ex: 0 4): ";
            std::cin >> de >> para;
        } else {
            // IA simples: ataca o primeiro território inimigo que encontrar se tiver tropas
            de = 3; para = 0; 
            std::cout << "IA atacando de " << mapa[de].nome << " para " << mapa[para].nome << "...\n";
        }

        // Validação e Simulação de Ataque
        if (de >= 0 && de < totalTerritorios && para >= 0 && para < totalTerritorios &&
            mapa[de].dono == atacanteAtual && mapa[para].dono != atacanteAtual && mapa[de].tropas > 1) {
            
            // 4. Geração de Números Aleatórios (Combate)
            int dadoAtk = (rand() % 6) + 1;
            int dadoDef = (rand() % 6) + 1;

            std::cout << "Dados: Atacante [" << dadoAtk << "] vs Defesa [" << dadoDef << "]\n";

            if (dadoAtk > dadoDef) {
                std::cout << "Vitoria no ataque!\n";
                mapa[para].tropas--;
                if (mapa[para].tropas <= 0) {
                    std::cout << "CONQUISTADO!\n";
                    mapa[para].dono = atacanteAtual;
                    mapa[para].tropas = 1;
                    mapa[de].tropas--;
                }
            } else {
                std::cout << "A defesa segurou o ataque!\n";
                mapa[de].tropas--;
            }
        } else {
            std::cout << "Comando invalido ou tropas insuficientes para atacar!\n";
        }

        // Verificar Condição de Vitória (Missão ou Conquista Total)
        int contagem = 0;
        for (int i = 0; i < totalTerritorios; i++) if (mapa[i].dono == 1) contagem++;
        
        if (contagem >= missaoJogador.metaTerritorios || contagem == totalTerritorios) {
            std::cout << "\nPARABENS! O JOGADOR VENCEU POR MISSAO!\n";
            jogoAtivo = false;
        } else if (contagem == 0) {
            std::cout << "\nA IA DOMINOU TUDO. FIM DE JOGO.\n";
            jogoAtivo = false;
        }

        turno++;
        if (turno > 20) jogoAtivo = false; // Trava de segurança
    }

    // 5. Liberação de memória com free
    free(mapa);
    std::cout << "\nMemoria desalocada. Saindo...\n";

    return 0;
}