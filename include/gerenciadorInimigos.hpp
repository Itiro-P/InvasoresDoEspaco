#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include <inimigo.hpp>
#include <enums.hpp>

class gerenciadorInimigos {
    std::array<float, 2> limites {0.f, 0.f};
    std::array<std::array<alien, 11>, 5> mapa;
    sf::Texture textura;
    sf::Vector2u resolucaoSistema;
    sf::Vector2f tamanhoSprite{16.f, 8.f};
    int inimigosVivos = 55;
    int qps;
    int contadorQuadros = 0;
    int spriteAtual = 0;
    const int spriteMorte = 2;
    float escala;
    float velocidade;
    float posTopoEsquerdoX;
    float posTopoEsquerdoY;
    enums::direcao direcao = enums::direcao::esquerda;

public:
    gerenciadorInimigos(const std::filesystem::path& caminhoTextura, const sf::Vector2u& resolucaoSistema, const int qps, const std::array<std::array<alien, 11>, 5>& mapaInimigos);
    void atualizarPosicao();
    std::array<std::array<alien, 11>, 5>& getMapa();
    void desenhar(sf::RenderWindow& janela);
};