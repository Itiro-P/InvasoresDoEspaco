#pragma once

#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include <enums.hpp>
#include <ator.hpp>
#include <projetil.hpp>
#include <recursoManager.hpp>


// Coordena os Aliens
class GerenciadorAliens {
    std::shared_ptr<RecursoManager> recursoManagerPtr = nullptr;
    int aliensVivos = 55;
    int contadorBalas = 0;
    int spriteAtual = 0;
    float velocidade;
    float posTopoEsquerdoX;
    float posTopoEsquerdoY;
    Direcao direcao = Direcao::Esquerda;


    std::array<std::array<Alien, 11>, 5> gridAliens {
        // triangulo
       std::array {
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Triangulo][0], Tipo::Triangulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Triangulo][0], Tipo::Triangulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Triangulo][0], Tipo::Triangulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Triangulo][0], Tipo::Triangulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Triangulo][0], Tipo::Triangulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Triangulo][0], Tipo::Triangulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Triangulo][0], Tipo::Triangulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Triangulo][0], Tipo::Triangulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Triangulo][0], Tipo::Triangulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Triangulo][0], Tipo::Triangulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Triangulo][0], Tipo::Triangulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala())
       },
    
       // circulo
       std::array {
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala())
       },
       std::array {
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Circulo][0], Tipo::Circulo, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala())
       },
    
       // quadrado
       std::array {
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala())
       },
       std::array {
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala()),
          Alien(recursoManagerPtr->getPosSpritesAliens()[Tipo::Quadrado][0], Tipo::Quadrado, sf::Vector2f{0.f, 0.f}, recursoManagerPtr->getTamanhoSprite(), recursoManagerPtr->getEscala())
       }
    };

public:
    GerenciadorAliens(RecursoManager &recursoManager);
    void moverGrid();
    void restaurarGrid();
    std::array<std::array<Alien, 11>, 5> getGridAliens() const { return gridAliens; };
    int getAliensVivos() const { return aliensVivos; };
    void setAliensVivos(const int valor) { aliensVivos = valor; };
};