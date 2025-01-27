#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include <inimigo.hpp>
#include <enums.hpp>

class gerenciadorInimigos {
    std::array<float, 2> limites {0.f, 0.f};
    std::array<sf::VertexArray, 5> vertices;
    std::array<std::array<alien, 11>, 5> mapaTipos;
    sf::Texture textura;
    sf::Vector2u resolucaoSistema;
    const float tamanhoSpriteX = 16.f;
    const float tamanhoSpriteY = 8.f;
    int qps;
    int contador = 0;
    int spriteAtual = 0;
    float escala;
    float velocidade;
    float posTopoEsquerdoX;
    float posTopoEsquerdoY;
    enums::direcao direcao = enums::direcao::esquerda;

public:
    gerenciadorInimigos(const std::filesystem::path& caminhoTextura, const sf::Vector2u& resolucaoSistema, const int qps, const std::array<std::array<alien, 11>, 5>& mapaTipos);
    void atualizarVertices();
    void desenhar(sf::RenderWindow& janela);
    alien getAlien(const int linha, const int coluna) const&;

private:
    void atualizarSprites(sf::Vertex* vertice, const int linha, const int coluna);
};