#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>
#include <gerenciadorInimigos.hpp>
#include <enums.hpp>


class janela;

class bala {
    sf::Vector2f posicao;
    sf::RectangleShape forma;
    float velocidade;
    float escala;
    int qps;

    public:
    bala(const sf::Vector2f& posicao, const float escala, const int qps);
    sf::FloatRect getRectBala() const&;
    sf::RectangleShape getForma() const&;
    sf::Vector2f getPosition() const&;
    void mover();
};

class jogador {
    sf::Vector2u resolucaoSistema;
    sf::Vector2u tamanhoSprite;
    sf::Texture textura;
    sf::Sprite sprite;
    int quantidadeSprites = 3;
    std::vector<sf::IntRect> posSprites;
    float velocidade;
    float escala;
    int qps;
    int mortes = 0;
    bool perdeu = 0;
    bool animando = 0;
    sf::Clock balaCooldown;
    std::vector<float> limites {0.f,0.f};

    std::vector<bala> balas;

    public:
    jogador(const sf::Vector2u& resolucaoSistema, const std::filesystem::path& caminhoTextura, const int quantidadeSprites, const std::vector<sf::IntRect>& posSprites, const sf::Vector2f& tamanhoSprite, const int qps);
    void atualizarBalas();
    bool getAnimando() const&;
    void mover(const enums::direcao dir);
    void atirar();
    void morte(const std::optional<std::reference_wrapper<janela>>& janela);
    void calcularColisao(gerenciadorInimigos& gerenciadorInimigos, janela& janela);
    void restaurarJogador(const std::optional<std::reference_wrapper<janela>>& janela = std::nullopt);
    std::vector<bala> getBalas() const&;
    sf::Vector2f getPosition() const&;
    void removerBalasForaDaTela();
    sf::Sprite getSprite() const&;
};