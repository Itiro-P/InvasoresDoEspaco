#pragma once

#include <erroManuseio.hpp>
#include <jogador.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <optional>
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
    void eventos(std::optional<jogador>& jogador = std::nullopt);
    void desenhar(const std::optional<jogador>& jogador = std::nullopt);
};