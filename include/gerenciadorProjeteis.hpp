#pragma once
#include <projetil.hpp>
#include <list>


// Classe que gerencia projeteis do jogador e aliens
class GerenciadorProjeteis {
    std::list<BalaAlien> balasAlien;
    std::list<BalaJogador> balasJogador;
    float escala;
    float velocidade;
    sf::Vector2u resolucaoSistema;

    public:
    GerenciadorProjeteis(const float escala, const float velocidade, const sf::Vector2u &resolucaoSistema) : escala(escala), velocidade(velocidade), resolucaoSistema(resolucaoSistema) {};
    std::list<BalaAlien> getBalasAlien() const { return balasAlien; };
    std::list<BalaJogador> getBalasJogador() const { return balasJogador; };
    void atirarJogador(const sf::Vector2f &posicao);
    void atirarAlien(const Tipo tipo, const std::array<sf::IntRect, 3> &posSprites, const sf::Texture &textura, const sf::Vector2f &posicao);
    void atualizarProjeteis();
    bool calcularColisoesJogador();
    Tipo calcularColisoesAlien();
};