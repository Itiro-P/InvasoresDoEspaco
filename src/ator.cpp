#include <erroManuseio.hpp>
#include <filesystem>
#include <string>
#include <ator.hpp>

Ator::Ator(const sf::Vector2f &posicaoInicial, const sf::Vector2i&tamanhoSprite, const float escala)
 : sprite(textura), posicaoInicial(posicaoInicial) {
    sprite.setOrigin(sf::Vector2f{tamanhoSprite.x/2.f, tamanhoSprite.y/2.f});
    sprite.setPosition(posicaoInicial);
    setEscala(escala);
}

bool Ator::checarColisao(Projetil &projetil) {
    return sprite.getGlobalBounds().contains(projetil.getPosicao());
}

void Ator::setPosicao(const sf::Vector2f &posicao) {
    sprite.setPosition(posicao);
}

void Ator::setEscala(const float escala) {
    sprite.setScale(sf::Vector2f{escala, escala});
}

void Ator::setSpriteAtual(const sf::IntRect &posSprite) {
    sprite.setTextureRect(posSprite);
}

Alien::Alien(const sf::IntRect &posSpritesInicial, const Tipo tipo, const sf::Vector2f &posicaoInicial, const sf::Vector2i &tamanhoSprite, const float escala)
 : Ator(posicaoInicial, tamanhoSprite, escala), tipo(tipo) {
    sprite.setTextureRect(posSpritesInicial);
}

void Alien::mover(const sf::Vector2f &deslocamento) {
    sprite.move(deslocamento);
}

void Alien::morte() {
    estado = Estado::Morrendo;
    
}

void Alien::restaurar() {
    sprite.setTextureRect(posSpritesInicial);
    estado = Estado::Vivo;
}

Jogador::Jogador(const sf::IntRect &posSpritesInicial, const sf::Vector2f &posicaoInicial, const sf::Vector2i &tamanhoSprite, const float escala, const float velocidade)
 : posSpritesInicial(posSpritesInicial), Ator(posicaoInicial, tamanhoSprite, escala), velocidade(velocidade) {
    sprite.setTextureRect(posSpritesInicial);
}

void Jogador::restaurar() {
    sprite.setTextureRect(posSpritesInicial);
    sprite.setPosition(posicaoInicial);
}

void Jogador::morte() {
    
}

void Jogador::mover(const Direcao direcao) {
    sprite.move(sf::Vector2f{(direcao == 1 ? velocidade : -velocidade), 0.f});
}
