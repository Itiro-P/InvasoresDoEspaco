#include <filesystem>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <jogador.hpp>
#include <janela.hpp>
#include <inimigo.hpp>
#include <gerenciadorInimigos.hpp>
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
    std::array<sf::Vector2f, 3> posSpritesTriangulo {
        sf::Vector2f { 1.f, 1.f },
        sf::Vector2f { 1.f, 11.f },
        sf::Vector2f { 55.f, 1.f }
    };

    std::array<sf::Vector2f, 3> posSpritesCirculo {
        sf::Vector2f { 19.f, 1.f },
        sf::Vector2f { 19.f, 11.f },
        sf::Vector2f { 55.f, 1.f }
    };

    std::array<sf::Vector2f, 3> posSpritesquadrado {
        sf::Vector2f { 37.f, 1.f },
        sf::Vector2f { 37.f, 11.f },
        sf::Vector2f { 55.f, 1.f }
    };

    std::array<std::array<alien, 11>, 5> mapaTipos;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 11; ++j) {
            switch (i) {
                case 0:
                    mapaTipos[i][j] = alien(enums::tipo::triangulo, posSpritesTriangulo, sf::Vector2f(16.f, 8.f));
                    break;
                case 1:
                case 2:
                    mapaTipos[i][j] = alien(enums::tipo::circulo, posSpritesCirculo, sf::Vector2f(16.f, 8.f));
                    break;
                case 3:
                case 4:
                    mapaTipos[i][j] = alien(enums::tipo::quadrado, posSpritesquadrado, sf::Vector2f(16.f, 8.f));
                    break;
            }
        }
    }

    gerenciadorInimigos gerenciadorInimigos(caminhoSprites, resolucao, qps, mapaTipos);

    // jogador
    const int quantidadeSprites = 3;
    std::vector<sf::IntRect> posSprites {
        sf::IntRect(sf::Vector2i(1, 49), sf::Vector2i(16, 8)),
        sf::IntRect(sf::Vector2i(19, 49), sf::Vector2i(16, 8)),
        sf::IntRect(sf::Vector2i(37, 49), sf::Vector2i(16, 8))
    };
    const sf::Vector2f tamanhoSprite(16.f, 8.f);

    janela janela(resolucao, caminhoIcone, caminhoFonte, vidasIniciais, pontosIniciais, qps);
    jogador jogador(resolucao, caminhoSprites, quantidadeSprites, posSprites, tamanhoSprite, qps);

    while (janela.getEstado()) {
        gerenciadorInimigos.animar();
        janela.eventos(jogador);
        janela.desenhar(jogador, gerenciadorInimigos);
    }

    return 0;
}