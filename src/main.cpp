#include <filesystem>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <jogador.hpp>
#include <janela.hpp>
#include <inimigo.hpp>

int main() {
    // caminhos de arquivos
    const std::filesystem::path caminhoIcone = "misc/icone.png";
    const std::filesystem::path caminhoSprites = "misc/sprites.png";
    const std::filesystem::path caminhoFonte = "misc/PixelifySans.ttf";

    // janela
    const sf::Vector2u resolucao(1280, 720);
    const int qps = 60; // padrao = 60
    const int vidasIniciais = 3; // padrao = 3
    const int pontosIniciais = 0; // padrao = 0

    // jogador
    const int quantidadeSprites = 3;
    std::vector<sf::IntRect> posSprites {
        sf::IntRect(sf::Vector2i(1, 49), sf::Vector2i(16, 8)),
        sf::IntRect(sf::Vector2i(19, 49), sf::Vector2i(16, 8)),
        sf::IntRect(sf::Vector2i(37, 49), sf::Vector2i(16, 8))
    };
    const sf::Vector2f tamanhoSprite(16.f, 8.f);

    janela janela(resolucao, caminhoIcone, caminhoFonte, vidasIniciais, pontosIniciais, qps);
    jogador jogador(resolucao, caminhoSprites, quantidadeSprites, posSprites, tamanhoSprite);
    while(janela.getEstado()) {
        janela.eventos(jogador);
        janela.desenhar(jogador);
    }
    return 0;
}