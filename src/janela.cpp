#include <janela.hpp>
#include <jogador.hpp>
#include <erroManuseio.hpp>
#include <SFML/Graphics.hpp>
#include <gerenciadorInimigos.hpp>
#include <filesystem>
#include <optional>
#include <enums.hpp>
#include <string>

janela::janela(const sf::Vector2u& resolucao, const std::filesystem::path& caminhoIcone, const std::filesystem::path& caminhoFonte, const int vidasIniciais, const int pontosIniciais, const int qps) 
: vidas(vidasIniciais), pontos(pontosIniciais), resolucao(resolucao), textoVidas(fonte), textoPontos(fonte), qps(qps) {
    if (!fonte.openFromFile(caminhoFonte.string())) erroArquivo(caminhoIcone.string());
    if (!icone.loadFromFile(caminhoIcone.string())) erroArquivo(caminhoFonte.string());
    instanciaJanela.create(sf::VideoMode({resolucao.x, resolucao.y}), L"Invasores do Espaço", sf::Style::Close);
    instanciaJanela.setFramerateLimit(qps);
    instanciaJanela.setIcon(icone);

    textoVidas.setString("Vidas: " + std::to_string(vidas));
    textoVidas.setFillColor(sf::Color::White);
    textoVidas.setCharacterSize(static_cast<unsigned int>(resolucao.x / 50));
    textoVidas.setPosition(sf::Vector2f({resolucao.x*0.85f , 10.f}));

    textoPontos.setString("Pontos: " + std::to_string(pontos));
    textoPontos.setFillColor(sf::Color::White);
    textoPontos.setCharacterSize(static_cast<unsigned int>(resolucao.x / 50));
    textoPontos.setPosition(sf::Vector2f({resolucao.x*0.01f , 10.f}));
}

bool janela::getEstado() const& {
    return instanciaJanela.isOpen();
}

void janela::eventos(std::optional<std::reference_wrapper<jogador>> jogador) {
    instanciaJanela.handleEvents(
        [this](const sf::Event::Closed) { instanciaJanela.close(); },
        [this, &jogador](const sf::Event::KeyPressed tecla) {
            switch (tecla.scancode) {
            case sf::Keyboard::Scancode::Escape:
                instanciaJanela.close();
                break;
            case sf::Keyboard::Scancode::Left:
                if(jogador.has_value()) jogador->get().mover(enums::direcao::esquerda);
                break;
            case sf::Keyboard::Scancode::Right:
                if(jogador.has_value()) jogador->get().mover(enums::direcao::direita);
                break;
            }
        }
    );
}

void janela::desenhar(const std::optional<std::reference_wrapper<jogador>>& jogador, const std::optional<std::reference_wrapper<gerenciadorInimigos>>& gerenciadorInimigos) {
    instanciaJanela.clear();
    instanciaJanela.draw(textoVidas);
    instanciaJanela.draw(textoPontos);
    if(jogador.has_value()) instanciaJanela.draw(jogador->get().getSprite());
    if(gerenciadorInimigos.has_value()) gerenciadorInimigos->get().desenhar(instanciaJanela);
    instanciaJanela.display();
}