#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>
#include <enums.hpp>

class jogador {
    sf::Vector2u resolucaoSistema;
    sf::Vector2u tamanhoSprite;
    sf::Texture textura;
    sf::Sprite sprite;
    int quantidadeSprites;
    std::vector<sf::IntRect> posSprites;
    float velocidade;
    float escala;
    int qps;
    std::vector<float> limites {0.f,0.f};

    public:
    jogador(const sf::Vector2u& resolucaoSistema, const std::filesystem::path& caminhoTextura, const int quantidadeSprites, const std::vector<sf::IntRect>& posSprites, const sf::Vector2f& tamanhoSprite, const int qps);
    void mover(const enums::direcao dir);
    void atirar();
    sf::Vector2f getPosicao() const&;
    sf::Sprite getSprite() const&;
};

class bala {
    sf::Vector2f posicao;
    float velocidade;
    float escala;
    int qps;
};