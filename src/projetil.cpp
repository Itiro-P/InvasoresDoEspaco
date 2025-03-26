#include <projetil.hpp>
#include <recursoManager.hpp>

Projetil::Projetil(const sf::Vector2f &posicao, const float velocidade, const float escala) : posicao(posicao), velocidade(velocidade), escala(escala) {
}

BalaJogador::BalaJogador(const sf::Vector2f &posicao, const float velocidade, const float escala) : Projetil(posicao, velocidade, escala) {
    forma.setPosition(sf::Vector2f(posicao.x, posicao.y*0.9f));
    forma.setSize(sf::Vector2f{1.f * escala, 4.f * escala});
    forma.setFillColor(sf::Color::White);
}

void BalaJogador::mover() {
    forma.move(sf::Vector2f{0.f, -velocidade});
}

BalaAlien::BalaAlien(const Tipo tipo, const std::array<sf::IntRect, 3> &posSprites, const sf::Texture &textura, const sf::Vector2f &posicao, const float velocidade, const float escala)
    : tipo(tipo), sprite(textura), posSprites(posSprites), Projetil(posicao, velocidade, escala) {
        sprite.setTextureRect(posSprites[spriteAtual]);
        sprite.setPosition(posicao);
        sprite.setScale(sf::Vector2f{escala, escala});
}

void BalaAlien::mover() {
    sprite.move(sf::Vector2f{0.f, velocidade});
    spriteAtual = (spriteAtual == 3 ? 0 : spriteAtual++);
    sprite.setTextureRect(posSprites[spriteAtual]);
}
