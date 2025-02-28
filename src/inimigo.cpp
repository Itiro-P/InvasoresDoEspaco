#include <inimigo.hpp>
#include <erroManuseio.hpp>
#include <enums.hpp>
#include <jogador.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <filesystem>

Alien::Alien(const Tipo tipo, const std::array<sf::Vector2i, 3> &posSprites, const sf::Texture& textura, const sf::Vector2i& tamanhoSprites, const std::array<sf::IntRect, 4>& posSpritesBalas) : 
tipo(tipo), posSprites(posSprites), sprite(textura), tamanhoSprites(tamanhoSprites), posSpritesBalas(posSpritesBalas) {
    if(sprite.has_value()) sprite->setTextureRect(sf::IntRect(posSprites[0], tamanhoSprites));
}

sf::FloatRect Alien::getRectAlien() const {
    return sf::FloatRect(sprite->getPosition(), sf::Vector2f{static_cast<float>(tamanhoSprites.x), static_cast<float>(tamanhoSprites.y)});
}

Tipo Alien::getTipo() const {
    return tipo;
}

Condicao Alien::getEstado() const {
    return estado;
}

void Alien::setPosition(const sf::Vector2f &posicao) {
    sprite->setPosition(posicao);
}

void Alien::setScale(const sf::Vector2f &scale) {
    sprite->setScale(scale);
}

void Alien::setRect(const int idx) {
    sprite->setTextureRect(sf::IntRect{posSprites[idx], tamanhoSprites});
}

void Alien::inimigoMover(const sf::Vector2f &velocidade) {
    sprite->move(velocidade);
}

void Alien::setEstado(const Condicao condicao) {
    estado = condicao;
}

sf::Vector2f Alien::getPosition() const {
    return sprite->getPosition();
}

std::array<sf::Vector2i, 3> Alien::getPosSprites() const {
    return posSprites;
}

std::array<sf::IntRect, 4> Alien::getPosSpritesBalas() const {
    return posSpritesBalas;
}

sf::Sprite Alien::getSprite() const {
    return sprite.value();
}

bool Alien::checarColisao(const Bala& bala) {
    bool colisaoX = bala.getPosition().x > sprite->getPosition().x && bala.getPosition().x < sprite->getPosition().x + sprite->getGlobalBounds().size.x;
    bool colisaoY = bala.getPosition().y < sprite->getPosition().y && bala.getPosition().y > sprite->getPosition().y - sprite->getGlobalBounds().size.y;
    return colisaoX && colisaoY;
}
