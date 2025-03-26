#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <enums.hpp>


// Tipo cru de projétil
class Projetil {
    protected:
    sf::Vector2f posicao;
    float velocidade;
    float escala;
    bool remover = false;

    public:
    Projetil(const sf::Vector2f &posicao, const float velocidade, const float escala);
    virtual void mover() = 0;
    virtual sf::Vector2f getPosicao() = 0;
    bool getRemover() const { return remover; };
    void setRemover(const bool remover) { this->remover = remover; };
};

// Projétil do Jogador
class BalaJogador : public Projetil{
    sf::RectangleShape forma;

    public:
    BalaJogador(const sf::Vector2f &posicao, const float velocidade, const float escala);
    sf::RectangleShape getForma() const { return forma; };
    void mover() override;
    sf::Vector2f getPosicao() override { return forma.getPosition(); };
};

// Projétil dos Aliens. Controlado pelo GerenciadorAlien
class BalaAlien : public Projetil {
    Tipo tipo;
    sf::Sprite sprite;
    std::array<sf::IntRect, 3> posSprites;
    int spriteAtual = 0;
    int cooldownQuadros;
    int contadorQuadros = 0;

    public:
    BalaAlien(const Tipo tipo, const std::array<sf::IntRect, 3> &posSprites, const sf::Texture &textura, const sf::Vector2f &posicao, const float velocidade, const float escala);
    sf::Sprite getSprite() const { return sprite; };
    Tipo getTipo() const { return tipo; };
    void mover() override;
    sf::Vector2f getPosicao() override { return sprite.getPosition(); };
};