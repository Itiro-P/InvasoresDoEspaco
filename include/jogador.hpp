#pragma once

#include <erroManuseio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <filesystem>
#include <vector>
#include <string>

enum direcao { esquerda = 0, direita = 1 };

class jogador {
    sf::Vector2u resolucaoSistema;
    sf::Vector2u tamanhoSprite;
    sf::Texture textura;
    sf::Sprite sprite;
    int quantidadeQuadros;
    std::vector<sf::Vector2f> posQuadros;
    float velocidade;
    std::vector<float> limites {0.f,0.f};

    public:
    jogador(const sf::Vector2u& resolucaoSistema, const std::filesystem::path& caminhoTextura, const int quantidadeQuadros, const std::vector<sf::Vector2f>& posQuadros, const sf::Vector2u& tamanhoSprite);
    void mover(const direcao dir);
    sf::Vector2f getPosicao() const&;
    sf::Sprite getSprite() const&;
};