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
    sf::Text vidas;
    sf::Text pontos;

    public:
    janela(const sf::Vector2u& resolucao, const std::filesystem::path& caminhoIcone, const std::filesystem::path& caminhoFonte);
    bool getEstado() const&;
    void eventos();
    void desenhar();
};

class JanelaException : public std::runtime_error {
    public:
    explicit JanelaException(const std::string& mensagem) : std::runtime_error(mensagem) {}
};