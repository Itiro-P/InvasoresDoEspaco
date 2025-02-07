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
: vidas(vidasIniciais), pontos(pontosIniciais), resolucao(resolucao), textoVidas(fonte), textoPontos(fonte), textoPerdeu(fonte), qps(qps) {
    if (!fonte.openFromFile(caminhoFonte.string())) erroArquivo(caminhoFonte.string());
    if (!icone.loadFromFile(caminhoIcone.string())) erroArquivo(caminhoIcone.string());
    instanciaJanela.create(sf::VideoMode({resolucao.x, resolucao.y}), L"Invasores do Espaço", sf::Style::Close);
    instanciaJanela.setFramerateLimit(qps);
    instanciaJanela.setIcon(icone);

    textoVidas.setString("Vidas: " + std::to_string(vidas));
    textoVidas.setFillColor(sf::Color::White);
    textoVidas.setCharacterSize(static_cast<unsigned int>(resolucao.x / 40));
    textoVidas.setPosition(sf::Vector2f({resolucao.x*0.85f , 10.f}));

    textoPontos.setString("Pontos: " + std::to_string(pontos));
    textoPontos.setFillColor(sf::Color::White);
    textoPontos.setCharacterSize(static_cast<unsigned int>(resolucao.x / 40));
    textoPontos.setPosition(sf::Vector2f({resolucao.x*0.01f , 10.f}));

    textoPerdeu.setFillColor(sf::Color::White);
    textoPerdeu.setCharacterSize(static_cast<unsigned int>(resolucao.x / 40));
    textoPerdeu.setOrigin(textoPerdeu.getGlobalBounds().size / 2.f);
    textoPerdeu.setPosition(sf::Vector2f{resolucao.x / 2.f, resolucao.y / 2.f});

}

bool janela::getEstado() const& {
    return instanciaJanela.isOpen();
}

void janela::perdeuJogo() {
    textoPerdeu.setString(L"Você perdeu.\nPontuação total: " + std::to_wstring(pontos) + L"\nPressione ENTER para recomeçar:");
}

void janela::restaurar() {
    vidas = 3;
    pontos = 0;
}

void janela::setPontuacao(const enums::tipo tipo) {
    switch (tipo) {
        case enums::tipo::circulo:
        pontos += 10;
        break;
        case enums::tipo::quadrado:
        pontos += 20;
        break;
        case enums::tipo::triangulo:
        pontos += 40;
        break;
    }
    textoPontos.setString("Pontos: " + std::to_string(pontos));
    if(pontos % 1500 == 0 && vidas < 3 && vidas != 0) {
        textoVidas.setString("Vidas: " + std::to_string(++vidas));
    }
}

bool janela::getTravar() const& {
    return travar;
}

void janela::setTravar() {
    travar = true;
}

void janela::eventos(std::optional<std::reference_wrapper<jogador>> jogador, std::optional<std::reference_wrapper<gerenciadorInimigos>> gerenciadorInimigos) {
    instanciaJanela.handleEvents(
        [this](const sf::Event::Closed) { instanciaJanela.close(); },
        [this, &jogador, &gerenciadorInimigos](const sf::Event::KeyPressed tecla) {
            if(jogador.has_value()) {
                if(tecla.scancode == sf::Keyboard::Scancode::Escape) instanciaJanela.close();
                if(tecla.scancode == sf::Keyboard::Scancode::Enter) {
                    restaurar();
                    jogador->get().restaurarJogador();
                    if(gerenciadorInimigos.has_value()) gerenciadorInimigos->get().restaurarPosicoes();
                }

                if(!travar) {
                    if(tecla.scancode == sf::Keyboard::Scancode::Left) jogador->get().mover(enums::direcao::esquerda);
                    if(tecla.scancode == sf::Keyboard::Scancode::Right) jogador->get().mover(enums::direcao::direita);
                    if(tecla.scancode == sf::Keyboard::Scancode::Space) jogador->get().atirar();
                }
            }
        }
    );
}

void janela::desenhar(const std::optional<std::reference_wrapper<jogador>>& jogador, const std::optional<std::reference_wrapper<gerenciadorInimigos>>& gerenciadorInimigos) {
    instanciaJanela.clear();
    instanciaJanela.draw(textoVidas);
    instanciaJanela.draw(textoPontos);
    if(jogador.has_value()) {
        instanciaJanela.draw(jogador->get().getSprite());
        for(const auto& bala: jogador->get().getBalas()) {
            instanciaJanela.draw(bala.getForma());
        }
    }
    if(gerenciadorInimigos.has_value()) gerenciadorInimigos->get().desenhar(instanciaJanela);
    instanciaJanela.display();
}