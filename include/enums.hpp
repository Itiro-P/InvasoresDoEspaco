#pragma once

#include <array>
#include <SFML/Graphics.hpp>

namespace enums {
    enum tipo { triangulo, circulo, quadrado };

    enum condicao { morto, vivo };

    enum direcao { esquerda, direita };
};

class alien {
    public:
    enums::tipo tipo;
    int quantidadeSprites = 3;
    std::array<sf::Vector2f, 3> posSprites;
    sf::Vector2f tamanhoSprite;
    
    alien(const enums::tipo tipo, const std::array<sf::Vector2f, 3>& posSprites, const sf::Vector2f& tamanhoSprite);
    alien() = default;
};