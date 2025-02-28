#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <enums.hpp>
#include <optional>

class Bala;

class Alien {
    Tipo tipo = Tipo::Circulo;
    Condicao estado = Condicao::Vivo;
    int quantidadeSprites = 3;
    std::optional<sf::Sprite> sprite;
    sf::Vector2i tamanhoSprites{16, 8};
    std::array<sf::Vector2i, 3> posSprites {
        sf::Vector2i{0, 0},
        sf::Vector2i{0, 0},
        sf::Vector2i{0, 0}
    };
    std::array<sf::IntRect, 4> posSpritesBalas;
    
    public:
    Alien() = default;
    Alien(const Tipo tipo, const std::array<sf::Vector2i, 3> &posSprites, const sf::Texture& textura, const sf::Vector2i& tamanhoSprites, const std::array<sf::IntRect, 4>& posSpritesBalas);
    sf::FloatRect getRectAlien() const;
    Tipo getTipo() const;
    Condicao getEstado() const;
    sf::Vector2f getPosition() const;
    std::array<sf::Vector2i, 3> getPosSprites() const;
    std::array<sf::IntRect, 4> getPosSpritesBalas() const;
    sf::Sprite getSprite() const;
    bool checarColisao(const Bala& bala);
    void setPosition(const sf::Vector2f& posicao);
    void setScale(const sf::Vector2f& scale);
    void setRect(const int idx);
    void inimigoMover(const sf::Vector2f& velocidade);
    void setEstado(const Condicao condicao);
};