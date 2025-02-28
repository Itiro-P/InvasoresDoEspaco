#pragma once

#include <GerenciadorInimigos.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <optional>
#include <string>
#include <enums.hpp>

class Jogador;

class Janela {
    sf::RenderWindow instanciaJanela;
    sf::Vector2u resolucao;
    sf::Image icone;
    sf::Font fonte;
    sf::Text textoVidas;
    sf::Text textoPontos;
    sf::Text textoPerdeu;
    int vidas;
    int pontos;
    int qps;
    bool travar = false;

    public:
    Janela(const sf::Vector2u& resolucao, const std::filesystem::path& caminhoIcone, const std::filesystem::path& caminhoFonte, const int vidasIniciais = 3, const int pontosIniciais = 0, const int qps = 60);
    bool getEstado() const;
    void perdeuJogo();
    void restaurar();
    void setPontuacao(const Tipo tipo);
    void updateVidas();
    bool getTravar() const;
    void setTravar(bool estado);
    void eventos(Jogador &jogador, GerenciadorInimigos &gerenciadorInimigos);
    void desenhar(Jogador &jogador, GerenciadorInimigos &gerenciadorInimigos);
};