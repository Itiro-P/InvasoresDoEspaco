#include <filesystem>
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <jogador.hpp>
#include <janela.hpp>
#include <inimigo.hpp>
#include <gerenciadorInimigos.hpp>
#include <erroManuseio.hpp>
#include <enums.hpp>

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

    // aliens
    const std::array<sf::Vector2i, 3> posSpritesTriangulo {
        sf::Vector2i { 1, 1 },
        sf::Vector2i { 1, 11 },
        sf::Vector2i { 55, 1 }
    };

    const std::array<sf::Vector2i, 3> posSpritesCirculo {
        sf::Vector2i { 19, 1 },
        sf::Vector2i { 19, 11 },
        sf::Vector2i { 55, 1 }
    };

    const std::array<sf::Vector2i, 3> posSpritesquadrado {
        sf::Vector2i { 37, 1 },
        sf::Vector2i { 37, 11 },
        sf::Vector2i { 55, 1 }
    };

    sf::Texture sprites;
    if(!sprites.loadFromFile(caminhoSprites)) erroArquivo(caminhoSprites.string());

    std::array<std::array<alien, 11>, 5> mapaInimigos;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 11; ++j) {
            switch (i) {
                case 0:
                    mapaInimigos[i][j] = alien(enums::tipo::triangulo, posSpritesTriangulo, sprites, sf::Vector2i(16, 8));
                    break;
                case 1:
                case 2:
                    mapaInimigos[i][j] = alien(enums::tipo::circulo, posSpritesCirculo, sprites, sf::Vector2i(16, 8));
                    break;
                case 3:
                case 4:
                    mapaInimigos[i][j] = alien(enums::tipo::quadrado, posSpritesquadrado, sprites, sf::Vector2i(16, 8));
                    break;
            }
        }
    }

    gerenciadorInimigos gerenciadorInimigos(caminhoSprites, resolucao, qps, mapaInimigos);

    // jogador
    const int quantidadeSprites = 3;
    const std::vector<sf::IntRect> posSprites {
        sf::IntRect(sf::Vector2i(1, 49), sf::Vector2i(16, 8)),
        sf::IntRect(sf::Vector2i(19, 49), sf::Vector2i(16, 8)),
        sf::IntRect(sf::Vector2i(37, 49), sf::Vector2i(16, 8))
    };
    const sf::Vector2f tamanhoSprite(16.f, 8.f);

    janela janela(resolucao, caminhoIcone, caminhoFonte, vidasIniciais, pontosIniciais, qps);
    jogador jogador(resolucao, caminhoSprites, quantidadeSprites, posSprites, tamanhoSprite, qps);

    while (janela.getEstado()) {
        if(gerenciadorInimigos.getInimigosVivos() == 0) {
            gerenciadorInimigos.restaurarPosicoes();
            jogador.restaurarJogador();
        }
        janela.eventos(jogador);
        jogador.atualizarBalas();
        jogador.calcularColisao(gerenciadorInimigos, janela);
        gerenciadorInimigos.atualizarPosicao();
        janela.desenhar(jogador, gerenciadorInimigos);
    }

    return 0;
}