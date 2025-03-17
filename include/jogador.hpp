#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>
#include <gerenciadorInimigos.hpp>
#include <enums.hpp>


class Interface;

class Bala {
    sf::Vector2f posicao;   
    sf::RectangleShape forma;
    float velocidade;
    float escala;
    int qps;

    public:
    Bala(const sf::Vector2f& posicao, const float escala, const int qps);
    sf::FloatRect getRectBala() const;
    sf::RectangleShape getForma() const;
    sf::Vector2f getPosition() const;
    void mover();
};


class Jogador {
    sf::Vector2u resolucaoSistema;
    sf::Vector2u tamanhoSprite;
    sf::Texture textura;
    sf::Sprite sprite;
    int quantidadeSprites = 3;
    std::vector<sf::IntRect> posSprites;
    float velocidade;
    float escala;
    int qps;
    bool animando = false;
    int spriteAtual = 0;
    sf::Clock balaCooldown;
    int contador = 0;
    int contador2 = 0;
    std::vector<float> limites {0.f,0.f};

    std::vector<Bala> balas;

    public:
    Jogador(const sf::Vector2u& resolucaoSistema, const std::filesystem::path& caminhoTextura, const int quantidadeSprites, const std::vector<sf::IntRect>& posSprites, const sf::Vector2f& tamanhoSprite, const int qps);
    void atualizarBalas();
    void mover(const Direcao dir);
    void atirar();
    void morte(Interface &janela);
    void calcularColisao(GerenciadorInimigos& GerenciadorInimigos, Interface& janela);
    void atualizarAnimacaoMorte(Interface& janela);
    void restaurarJogador();
    std::vector<Bala> getBalas() const;
    sf::Vector2f getPosition() const;
    void removerBalasForaDaTela();
    sf::Sprite getSprite() const;
    bool getAnimando() { return animando; };
    bool animacaoConcluida() { return contador2 >= qps*2; };
};