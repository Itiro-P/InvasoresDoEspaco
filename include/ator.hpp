#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <enums.hpp>
#include <projetil.hpp>
#include <recursoManager.hpp>
#include <texturaManager.hpp>


// Classe básica de qualquer objeto animado
class Ator {
    protected:  
    sf::Texture &textura = TexturaManager::getTextura(dir::CaminhoSprites); // TexturaManager has not been declared
    sf::Sprite sprite;
    sf::Vector2f posicaoInicial;
    public:
    Ator(const sf::Vector2f &posicaoInicial, const sf::Vector2i &tamanhoSprite, const float escala);
    bool checarColisao(Projetil &projetil);
    void setPosicao(const sf::Vector2f &posicao);
    void setEscala(const float escala);
    virtual void morte() = 0;
    sf::Vector2f getPosicao() const { return sprite.getPosition(); };
    sf::Sprite getSprite() const { return sprite; };
    void setSpriteAtual(const sf::IntRect &posSprite);
    virtual void restaurar() = 0;
};

// Ramificação do Ator, um objeto animado que é movido por GerenciadorAlien
class Alien : public Ator {
    Tipo tipo = Tipo::Circulo;
    Estado estado = Estado::Vivo;
    sf::IntRect posSpritesInicial;

    public:
    Alien(const sf::IntRect &posSpritesInicial, const Tipo tipo, const sf::Vector2f &posicaoInicial, const sf::Vector2i &tamanhoSprite, const float escala);
    void mover(const sf::Vector2f &deslocamento);
    Tipo getTipo() { return tipo; };
    void morte() override;
    Estado getEstado() const { return estado; };
    void setTipo(const Tipo tipo) { this->tipo = tipo; };
    void setEstado(const Estado estado) { this->estado = estado; };
    void restaurar() override;
};

// Ramificação do Ator, representação do jogador
class Jogador : public Ator {
    bool animando = false;
    int contador = 0;
    int contador2 = 0;
    sf::IntRect posSpritesInicial;
    float velocidade = 0.f;

    public:
    Jogador(const sf::IntRect &posSpritesInicial, const sf::Vector2f &posicaoInicial, const sf::Vector2i &tamanhoSprite, const float escala, const float velocidade);
    void restaurar() override;
    void morte() override;
    void mover(const Direcao direcao);
};