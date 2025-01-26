#pragma once

#include <vector>
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
    std::vector<sf::Vector2f> posSprites;
    sf::Vector2f tamanhoSprite;
    
    alien(const enums::tipo tipo, const std::vector<sf::Vector2f>& posSprites, const sf::Vector2f& tamanhoSprite);
    alien() = default;
};