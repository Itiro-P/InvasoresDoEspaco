#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <enums.hpp>
#include <optional>

class bala;

class alien {
    enums::tipo tipo = enums::tipo::circulo;
    enums::condicao estado = enums::condicao::vivo;
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
    alien() = default;
    alien(const enums::tipo tipo, const std::array<sf::Vector2i, 3> &posSprites, const sf::Texture& textura, const sf::Vector2i& tamanhoSprites, const std::array<sf::IntRect, 4>& posSpritesBalas);
    sf::FloatRect getRectAlien() const&;
    enums::tipo getTipo() const&;
    enums::condicao getEstado() const&;
    sf::Vector2f getPosition() const&;
    std::array<sf::Vector2i, 3> getPosSprites() const&;
    std::array<sf::IntRect, 4> getPosSpritesBalas() const&;
    sf::Sprite getSprite() const&;
    bool checarColisao(const bala& bala);
    void setPosition(const sf::Vector2f& posicao);
    void setScale(const sf::Vector2f& scale);
    void setRect(const int idx);
    void inimigoMover(const sf::Vector2f& velocidade);
    void setEstado(const enums::condicao condicao);
};