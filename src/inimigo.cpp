#include <inimigo.hpp>
#include <erroManuseio.hpp>
#include <enums.hpp>
#include <jogador.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <filesystem>

alien::alien(const enums::tipo tipo, const std::array<sf::Vector2i, 3> &posSprites, const sf::Texture& textura, const sf::Vector2i& tamanhoSprites) : 
tipo(tipo), posSprites(posSprites), sprite(textura), tamanhoSprites(tamanhoSprites) {
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
    // Verifica se o estado atual permite a alteração
    if (estado != enums::condicao::morto) {
        estado = condicao;
    }
}

sf::Vector2f alien::getPosition() const& {
    return sprite->getPosition();
}

std::array<sf::Vector2i, 3> alien::getPosSprites() const & {
    return posSprites;
}

sf::Sprite alien::getSprite() const& {
    return sprite.value();
}

bool alien::checarColisao(const bala& bala) {
    bool colisaoX = bala.getPosition().x > sprite->getPosition().x && bala.getPosition().x < sprite->getPosition().x + sprite->getGlobalBounds().size.x;
    bool colisaoY = bala.getPosition().y <= sprite->getPosition().y ;
    return colisaoX && colisaoY;
}
