#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <stdexcept>
#include <string>

class janela {
    sf::RenderWindow instanciaJanela;
    sf::Vector2u resolucao;
    sf::Image icone;
    sf::Font fonte;
    sf::Text textoVidas;
    sf::Text textoPontos;
    int vidas;
    int pontos;

    public:
    janela(const sf::Vector2u& resolucao, const std::filesystem::path& caminhoIcone, const std::filesystem::path& caminhoFonte, const int vidasIniciais = 3, const int pontosIniciais = 0);
    bool getEstado() const&;
    void eventos();
    void desenhar();
};

class JanelaException : public std::runtime_error {
    public:
    explicit JanelaException(const std::string& mensagem) : std::runtime_error(mensagem) {}
};