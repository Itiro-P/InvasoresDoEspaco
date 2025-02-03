#include <inimigo.hpp>
#include <erroManuseio.hpp>
#include <enums.hpp>
#include <jogador.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <filesystem>

alien::alien(const enums::tipo tipo, const std::array<sf::Vector2i, 3> &posSprites, const sf::Texture& textura, const sf::Vector2i& tamanhoSprites, const std::array<sf::IntRect, 4>& posSpritesBalas) : 
tipo(tipo), posSprites(posSprites), sprite(textura), tamanhoSprites(tamanhoSprites), posSpritesBalas(posSpritesBalas) {
    if(sprite.has_value()) sprite->setTextureRect(sf::IntRect(posSprites[0], tamanhoSprites));
}

sf::FloatRect alien::getRectAlien() const& {
    return sf::FloatRect(sprite->getPosition(), sf::Vector2f{static_cast<float>(tamanhoSprites.x), static_cast<float>(tamanhoSprites.y)});
}

enums::tipo alien::getTipo() const& {
    return tipo;
}

enums::condicao alien::getEstado() const& {
    return estado;
}

void alien::setPosition(const sf::Vector2f &posicao) {
    sprite->setPosition(posicao);
}

void alien::setScale(const sf::Vector2f &scale) {
    sprite->setScale(scale);
}

void alien::setRect(const int idx) {
    sprite->setTextureRect(sf::IntRect{posSprites[idx], tamanhoSprites});
}

void alien::inimigoMover(const sf::Vector2f &velocidade) {
    sprite->move(velocidade);
}

void alien::setEstado(const enums::condicao condicao) {
    estado = condicao;
}

sf::Vector2f alien::getPosition() const& {
    return sprite->getPosition();
}

std::array<sf::Vector2i, 3> alien::getPosSprites() const & {
    return posSprites;
}

std::array<sf::IntRect, 4> alien::getPosSpritesBalas() const& {
    return posSpritesBalas;
}

sf::Sprite alien::getSprite() const& {
    return sprite.value();
}

bool alien::checarColisao(const bala& bala) {
    bool colisaoX = bala.getPosition().x > sprite->getPosition().x && bala.getPosition().x < sprite->getPosition().x + sprite->getGlobalBounds().size.x;
    bool colisaoY = bala.getPosition().y < sprite->getPosition().y && bala.getPosition().y > sprite->getPosition().y - sprite->getGlobalBounds().size.y;
    return colisaoX && colisaoY;
}
