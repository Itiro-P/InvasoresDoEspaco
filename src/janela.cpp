#include <janela.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <stdexcept>
#include <string>

janela::janela(const sf::Vector2u& resolucao, const std::filesystem::path& caminhoIcone, const std::filesystem::path& caminhoFonte, const int vidasIniciais, const int pontosIniciais) 
: vidas(vidasIniciais), pontos(pontosIniciais), resolucao(resolucao), textoVidas(fonte), textoPontos(fonte) {
    try {
        if (!fonte.openFromFile(caminhoFonte.string())) {
            throw JanelaException("erro ao carregar a fonte " + caminhoFonte.string() + ".\nVerifique se o arquivo existe.\n");
            std::cin.get();
        }
        if (!icone.loadFromFile(caminhoIcone.string())) {
            throw JanelaException("erro ao carregar o icone " + caminhoIcone.string() + ".\nVerifique se o arquivo existe.\n");
            std::cin.get();
        }
        instanciaJanela.create(sf::VideoMode({resolucao.x, resolucao.y}), L"Invasores do Espaço", sf::Style::Close);
        instanciaJanela.setIcon(icone);

        textoVidas.setString("Vidas: " + std::to_string(vidas));
        textoVidas.setFillColor(sf::Color::White);
        textoVidas.setCharacterSize(static_cast<unsigned int>(resolucao.x / 50));
        textoVidas.setPosition(sf::Vector2f({static_cast<float>(resolucao.x*0.85) , 10.f}));


        textoPontos.setString("Pontos: " + std::to_string(pontos));
        textoPontos.setFillColor(sf::Color::White);
        textoPontos.setCharacterSize(static_cast<unsigned int>(resolucao.x / 50));
        textoPontos.setPosition(sf::Vector2f({20.f , 10.f}));

    } catch (const JanelaException& e) {
        std::cerr << L"Erro ao inicializar a janela: " << e.what() << std::endl;
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
    instanciaJanela.draw(textoVidas);
    instanciaJanela.draw(textoPontos);
    instanciaJanela.display();
}


