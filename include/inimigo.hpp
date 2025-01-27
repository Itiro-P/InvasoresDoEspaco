#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <enums.hpp>

class alien {
    enums::tipo tipo;
    enums::condicao estado = enums::condicao::vivo;
    int quantidadeSprites = 3;
    std::array<sf::Vector2f, 3> posSprites;
    sf::Vector2f tamanhoSprite;
    
    public:
    alien(const enums::tipo tipo, const std::array<sf::Vector2f, 3>& posSprites, const sf::Vector2f& tamanhoSprite);
    enums::tipo getTipo() const&;
    enums::condicao getEstado() const&;
    std::array<sf::Vector2f, 3> getPosSprites() const&;
    alien() = default;
};