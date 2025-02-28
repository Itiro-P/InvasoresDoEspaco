#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include <inimigo.hpp>
#include <enums.hpp>

class Jogador;

class Janela;

class BalaInimigo {
    sf::Vector2f posicao;
    sf::Texture textura;
    sf::Sprite sprite;
    std::array<sf::IntRect, 4> posSprites;
    int spriteAtual = 0;
    float velocidade;
    float escala;
    int qps;
    int cooldownQuadros;
    int contadorQuadros = 0;

    public:
    BalaInimigo(const sf::Vector2f& posicao, const float escala, const int qps, const sf::Texture& textura, const std::array<sf::IntRect, 4>& posSprites);
    sf::Sprite getSprite() const;
    sf::Vector2f getPosition() const;
    void mover();
};

class GerenciadorInimigos {
    std::array<float, 2> limites {0.f, 0.f};
    std::array<std::array<Alien, 11>, 5> mapa;
    sf::Texture textura;
    sf::Vector2u resolucaoSistema;
    sf::Vector2f tamanhoSprite{16.f, 8.f};
    int inimigosVivos = 55;
    int qps;
    int contadorQuadros = 0;
    int contadorBalas = 0;
    int spriteAtual = 0;
    const int spriteMorte = 2;
    float escala;
    float velocidade;
    float posTopoEsquerdoX;
    float posTopoEsquerdoY;
    std::vector<BalaInimigo> balasInimigo;
    Direcao direcao = Direcao::Esquerda;

public:
    GerenciadorInimigos(const std::filesystem::path& caminhoTextura, const sf::Vector2u& resolucaoSistema, const int qps, const std::array<std::array<Alien, 11>, 5>& mapaInimigos);
    void atualizarPosicao();
    void atualizarBalas();
    void restaurarPosicoes();
    void atirar();
    void calcularColisaoBalaInimigo(Jogador& jogador, Janela& janela);
    int getInimigosVivos() const;
    std::array<std::array<Alien, 11>, 5>& getMapa();
    void desenhar(sf::RenderWindow& janela);
};