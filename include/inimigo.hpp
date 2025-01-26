#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <enums.hpp>

class inimigo {
    alien tipo;
    enums::condicao estado = enums::condicao::vivo;
    sf::Vector2f posicao;

    public:
    inimigo(const alien& alien, const sf::Vector2f& posicao);
    enums::condicao getEstado() const&;
    enums::tipo getTipo() const&;
    void setEstado(enums::condicao estado);
};