#include <iostream>
#include <vector>
#include <algorithm>

struct Territorio {
    std::string nome;
    int donoID;
    int tropas;
};

// Exemplo simplificado de combate
void resolverAtaque(Territorio& atacante, Territorio& defensor) {
    if (atacante.tropas <= 1) {
        std::cout << "Ataque impossivel: tropas insuficientes." << std::endl;
        return;
    }

    // Lógica simplificada: vence quem tem mais tropas (em um jogo real, use dados)
    if (atacante.tropas > defensor.tropas + 1) {
        std::cout << "Territorio " << defensor.nome << " conquistado!" << std::endl;
        defensor.donoID = atacante.donoID;
        defensor.tropas = atacante.tropas - 1;
        atacante.tropas = 1;
    } else {
        std::cout << "Ataque falhou!" << std::endl;
        atacante.tropas = 1; // Penalidade por derrota
    }
}