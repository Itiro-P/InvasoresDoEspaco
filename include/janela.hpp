#pragma once

#include <gerenciadorInimigos.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <optional>
#include <string>
#include <enums.hpp>

class jogador;

class janela {
    sf::RenderWindow instanciaJanela;
    sf::Vector2u resolucao;
    sf::Image icone;
    sf::Font fonte;
    sf::Text textoVidas;
    sf::Text textoPontos;
    int vidas;
    int pontos;
    int qps;

    public:
    janela(const sf::Vector2u& resolucao, const std::filesystem::path& caminhoIcone, const std::filesystem::path& caminhoFonte, const int vidasIniciais = 3, const int pontosIniciais = 0, const int qps = 60);
    bool getEstado() const&;
    void restaurar();
    void setPontuacao(const enums::tipo tipo);
    void eventos(std::optional<std::reference_wrapper<jogador>> jogador = std::nullopt);
    void desenhar(const std::optional<std::reference_wrapper<jogador>>& jogador = std::nullopt, const std::optional<std::reference_wrapper<gerenciadorInimigos>>& gerenciadorInimigos = std::nullopt);
};