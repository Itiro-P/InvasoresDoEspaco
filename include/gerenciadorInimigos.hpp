#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <inimigo.hpp>
#include <enums.hpp>

class gerenciadorInimigos {
    std::vector<inimigo> inimigos;
    std::vector<float> limites {0.f, 0.f};
    sf::VertexArray vertices;
    sf::Texture textura;
    sf::Vector2u resolucaoSistema;
    float escala;
    float velocidade;
    float posicaoPrimeirox;
    float posicaoPrimeiroy;
    enums::direcao direcao = enums::direcao::esquerda;

public:
    gerenciadorInimigos(const std::filesystem::path& caminhoTextura, const sf::Vector2u& resolucaoSistema, const int qps, const std::vector<std::vector<alien>>& mapaTipos);
    void desenhar(sf::RenderWindow& janela);
};