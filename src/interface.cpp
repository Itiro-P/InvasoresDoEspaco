#include <interface.hpp>
#include <jogador.hpp>
#include <erroManuseio.hpp>
#include <SFML/Graphics.hpp>
#include <gerenciadorInimigos.hpp>
#include <filesystem>
#include <enums.hpp>
#include <string>

Interface::Interface(const sf::Vector2u& resolucao, const std::filesystem::path& caminhoIcone, const std::filesystem::path& caminhoFonte, const int vidasIniciais, const int pontosIniciais, const int qps) 
: vidas(vidasIniciais), pontos(pontosIniciais), resolucao(resolucao), textoVidas(fonte), textoPontos(fonte), textoPerdeu(fonte), qps(qps) {
    if (!fonte.openFromFile(caminhoFonte.string())) erroArquivo(caminhoFonte.string());
    if (!icone.loadFromFile(caminhoIcone.string())) erroArquivo(caminhoIcone.string());
    janela.create(sf::VideoMode({resolucao.x, resolucao.y}), L"Invasores do Espaço", sf::Style::Close);
    janela.setFramerateLimit(qps);
    janela.setIcon(icone);

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
    textoPerdeu.setPosition(sf::Vector2f{resolucao.x / 2.f, 10.f});

}

bool Interface::getEstado() const {
    return janela.isOpen();
}

void Interface::perdeuJogo() {
    textoPerdeu.setString(L"Você perdeu.\nPontuação total: " + std::to_wstring(pontos) + L"\nPressione ENTER para recomeçar:");
}

void Interface::restaurar() {
    if(vidas == 0) vidas = 3;
    setPontuacao(Tipo::Reset);
    textoPerdeu.setString(L"");
    setTravar(0);
}

void Interface::setPontuacao(const Tipo tipo) {
    switch (tipo) {
        case Tipo::Circulo:
        pontos += 10;
        break;
        case Tipo::Quadrado:
        pontos += 20;
        break;
        case Tipo::Triangulo:
        pontos += 40;
        break;
        case Tipo::Reset:
        pontos = 0;
        break;
    }
    textoPontos.setString("Pontos: " + std::to_string(pontos));
    if(pontos != 0 && pontos % 1500 == 0 && vidas < 3 && vidas != 0) {
        textoVidas.setString("Vidas: " + std::to_string(++vidas));
    }
}

void Interface::updateVidas() {
    if(vidas > 0) --vidas;
    textoVidas.setString("Vidas: " + std::to_string(vidas));
}

bool Interface::getTravar() const {
    return travar;
}

void Interface::setTravar(bool estado) {
    travar = estado;
}

void Interface::eventos(Jogador &jogador, GerenciadorInimigos &gerenciadorInimigos) {
    if(travar && vidas > 0) {
        if(jogador.animacaoConcluida()) {
            restaurar();
            jogador.restaurarJogador();
            gerenciadorInimigos.restaurarPosicoes();
        }
    }
    janela.handleEvents(
        [this](const sf::Event::Closed) { janela.close(); },
        [this, &jogador, &gerenciadorInimigos](const sf::Event::KeyPressed tecla) {
            if(tecla.scancode == sf::Keyboard::Scancode::Escape) janela.close();
            if(tecla.scancode == sf::Keyboard::Scancode::Enter && travar) {
                if((jogador.animacaoConcluida())) {
                    restaurar();
                    jogador.restaurarJogador();
                    setVidas(3);
                    textoVidas.setString("Vidas: " + std::to_string(vidas));
                    gerenciadorInimigos.restaurarPosicoes();
                }
            }

            if(!travar) {
                if(tecla.scancode == sf::Keyboard::Scancode::Left) jogador.mover(Direcao::Esquerda);
                if(tecla.scancode == sf::Keyboard::Scancode::Right) jogador.mover(Direcao::Direita);
                if(tecla.scancode == sf::Keyboard::Scancode::Space) jogador.atirar();
            }
        }
    );
}

void Interface::desenhar(Jogador &jogador, GerenciadorInimigos &gerenciadorInimigos) {
    janela.clear();
    janela.draw(textoVidas);
    janela.draw(textoPontos);
    if(jogador.animacaoConcluida() && travar && vidas == 0) {
        perdeuJogo();
        janela.draw(textoPerdeu);
    }
    janela.draw(jogador.getSprite());
    for(const auto& bala: jogador.getBalas()) {
        janela.draw(bala.getForma());
    }
    gerenciadorInimigos.desenhar(janela);
    janela.display();
}