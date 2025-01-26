#include <inimigo.hpp>
#include <erroManuseio.hpp>
#include <enums.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <filesystem>

inimigo::inimigo(const alien& alien, const sf::Vector2f& posicao) : tipo(alien), posicao(posicao) {}

enums::condicao inimigo::getEstado() const& {
    return estado;
}

enums::tipo inimigo::getTipo() const& {
    return tipo.tipo;
}

void inimigo::setEstado(enums::condicao novoEstado) {
    estado = novoEstado;
}
