#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <enums.hpp>

class alien {
    public:
    enums::tipo tipo;
    int quantidadeSprites = 3;
    std::array<sf::Vector2f, 3> posSprites;
    sf::Vector2f tamanhoSprite;
    
    alien(const enums::tipo tipo, const std::array<sf::Vector2f, 3>& posSprites, const sf::Vector2f& tamanhoSprite);
    alien() = default;
};