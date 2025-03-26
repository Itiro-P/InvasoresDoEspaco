#pragma once

#include <ator.hpp>
#include <erroManuseio.hpp>

// Classe contendo configuracoes do jogo (ex: resolucao, fps, etc)
class RecursoManager {
    const sf::Vector2i tamanhoSprite{16, 8};
    const sf::Vector2i tamanhoSpriteBala{3, 8};
    const sf::Vector2u resolucaoSistema{1280, 720};
    const int quantidadeSprites = 3;

    const int qps = 60;

    const std::array<sf::IntRect, 3> posSpritesJogador {
        sf::IntRect{sf::Vector2i{1, 49}, tamanhoSprite},
        sf::IntRect{sf::Vector2i{19, 49},tamanhoSprite},
        sf::IntRect{sf::Vector2i{37, 49}, tamanhoSprite}
    };
    const std::array<std::array<sf::IntRect, 3>, 3> posSpritesAliens {
        std::array {  // triangulo
            sf::IntRect{sf::Vector2i {1, 1}, tamanhoSprite},
            sf::IntRect{sf::Vector2i {1, 11}, tamanhoSprite},
            sf::IntRect{sf::Vector2i {55, 1}, tamanhoSprite}
        },
        std::array {  // circulo
            sf::IntRect{sf::Vector2i {19, 1}, tamanhoSprite}, 
            sf::IntRect{sf::Vector2i {19, 11}, tamanhoSprite},
            sf::IntRect{sf::Vector2i {55, 1}, tamanhoSprite}
        },
        std::array {  // quadrado
            sf::IntRect{sf::Vector2i {37, 1}, tamanhoSprite},
            sf::IntRect{sf::Vector2i {37, 11}, tamanhoSprite},
            sf::IntRect{sf::Vector2i {55, 1}, tamanhoSprite}
        }
    };
    const std::array<std::array<sf::IntRect, 4>, 3> posBalasAliens {
        std::array { // triangulo
            sf::IntRect{sf::Vector2i{1, 21}, tamanhoSpriteBala},
            sf::IntRect{sf::Vector2i{6, 21}, tamanhoSpriteBala},
            sf::IntRect{sf::Vector2i{11, 21}, tamanhoSpriteBala},
            sf::IntRect{sf::Vector2i{16, 21}, tamanhoSpriteBala}
        },
        std::array { // circulo
            sf::IntRect{sf::Vector2i{21, 21}, tamanhoSpriteBala},
            sf::IntRect{sf::Vector2i{26, 21}, tamanhoSpriteBala},
            sf::IntRect{sf::Vector2i{31, 21}, tamanhoSpriteBala},
            sf::IntRect{sf::Vector2i{36, 21}, tamanhoSpriteBala}
        },
        std::array { // quadrado
            sf::IntRect{sf::Vector2i{41, 21}, tamanhoSpriteBala},
            sf::IntRect{sf::Vector2i{46, 21}, tamanhoSpriteBala},
            sf::IntRect{sf::Vector2i{51, 21}, tamanhoSpriteBala},
            sf::IntRect{sf::Vector2i{56, 21}, tamanhoSpriteBala}
        },
    };

    std::array<float, 2> limitesTela;

    float escala;
    sf::Vector2f posicaoInicialJogador;
    float velocidadeBalas;
    float velocidade;

    public:
    RecursoManager();

    sf::Vector2i getTamanhoSprite() const { return tamanhoSprite;};
    sf::Vector2i getTamanhoSpriteBala() const { return tamanhoSpriteBala; };
    sf::Vector2u getResolucaoSistema() const { return resolucaoSistema; };
    int getQuantidadeSprites() const { return quantidadeSprites; };
    int getQps() { return qps; };

    std::array<sf::IntRect, 3> getPosSpritesJogador() const { return posSpritesJogador; };

    std::array<std::array<sf::IntRect, 3>, 3> getPosSpritesAliens() const { return posSpritesAliens; };

    std::array<std::array<sf::IntRect, 4>, 3> getPosBalasAliens() const { return posBalasAliens; };

    std::array<float, 2> getLimitesTela() const { return limitesTela; };

    float getEscala() const { return escala; };
    sf::Vector2f getPosicaoInicialJogador() const { return posicaoInicialJogador; };
    float getVelocidadeBalas() const { return velocidadeBalas; };
    float getVelocidade() const { return velocidade; };
};