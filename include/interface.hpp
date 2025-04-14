#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <enums.hpp>
#include <ator.hpp>
#include <gerenciadorAliens.hpp>
#include <gerenciadorProjeteis.hpp>
#include <recursoManager.hpp>
#include <estadoJogador.hpp>

// Faz a lógica de jogo e renderiza a tela
class Interface {
    std::shared_ptr<RecursoManager> recursoManagerPtr = nullptr;
    std::unique_ptr<GerenciadorAliens> gerenciadorAliensPtr = nullptr;
    std::unique_ptr<GerenciadorProjeteis> gerenciadorProjeteisPtr = nullptr;
    std::unique_ptr<Jogador> jogadorPtr = nullptr;
    std::unique_ptr<EstadoJogador> estadoJogadorPtr = nullptr;
    sf::RenderWindow janela;
    sf::Clock relogio;
    sf::Image icone;
    sf::Font fonte;
    sf::Text textoVidas;
    sf::Text textoPontos;
    sf::Text textoPerdeu;
    bool travar = false;

    public:
    Interface(RecursoManager &recursoManager, GerenciadorAliens &gerenciadorAliens, GerenciadorProjeteis &gerenciadorProjeteis, Jogador &jogador, EstadoJogador &estadoJogador);
    bool getEstado() const;
    void perdeuJogo();
    void restaurar();
    void setPontuacao(const Tipo tipo);
    void updateVidas();
    void atualizarProjeteis();
    void atualizarColisoes();
    bool getTravar() const;
    void setTravar(bool estado);
    void eventos();
    void desenhar();
};