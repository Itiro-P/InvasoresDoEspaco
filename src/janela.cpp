#include <janela.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <stdexcept>
#include <string>

janela::janela(const sf::Vector2u& resolucao, const std::filesystem::path& caminhoIcone, const std::filesystem::path& caminhoFonte) : resolucao(resolucao), vidas(fonte), pontos(fonte) {
    try {
        if (!fonte.openFromFile(caminhoFonte.string())) {
            throw JanelaException("erro ao carregar a fonte " + caminhoFonte.string() + ".\nVerifique se o arquivo existe.\n");
            std::cin.get();
        }
        if (!icone.loadFromFile(caminhoIcone.string())) {
            throw JanelaException("erro ao carregar o icone " + caminhoIcone.string() + ".\nVerifique se o arquivo existe.\n");
            std::cin.get();
        }
        instanciaJanela.create(sf::VideoMode({resolucao.x, resolucao.y}), "Invasores do Espaco", sf::Style::Close);
        instanciaJanela.setIcon(icone);

        vidas.setString("Vidas: 0");
        vidas.setFillColor(sf::Color::White);
        vidas.setCharacterSize(static_cast<unsigned int>(resolucao.x / 20));

        pontos.setString("Pontuação: 0");
        pontos.setFillColor(sf::Color::White);
        pontos.setCharacterSize(static_cast<unsigned int>(resolucao.x / 20));
    } catch (const JanelaException& e) {
        std::cerr << "Erro ao inicializar a janela: " << e.what() << std::endl;
        std::cin.get();
        throw;
    }
}

bool janela::getEstado() const& {
    return instanciaJanela.isOpen();
}

void janela::eventos() {
    instanciaJanela.handleEvents(
        [this](const sf::Event::Closed) { instanciaJanela.close(); },
        [this](const sf::Event::KeyPressed tecla) {
            switch (tecla.scancode) {
            case sf::Keyboard::Scancode::Escape:
                instanciaJanela.close();
                break;
            
            default:
                break;
            }
        }
    );
}

void janela::desenhar() {
    instanciaJanela.clear();
    instanciaJanela.display();
}


