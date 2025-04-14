#include <interface.hpp>
#include <erroManuseio.hpp>
#include <filesystem>
#include <string>

Interface::Interface(RecursoManager &recursoManager, GerenciadorAliens &gerenciadorAliens, GerenciadorProjeteis &gerenciadorProjeteis, Jogador &jogador, EstadoJogador &estadoJogador)
: recursoManagerPtr(std::make_shared<RecursoManager>(recursoManager)), 
    gerenciadorAliensPtr(std::make_unique<GerenciadorAliens>(std::move(gerenciadorAliens))), 
    gerenciadorProjeteisPtr(std::make_unique<GerenciadorProjeteis>(std::move(gerenciadorProjeteis))), 
    jogadorPtr(std::make_unique<Jogador>(std::move(jogador))), 
    estadoJogadorPtr(std::make_unique<EstadoJogador>(std::move(estadoJogador))), textoVidas(fonte), textoPontos(fonte), textoPerdeu(fonte) {
    if (!fonte.openFromFile(dir::CaminhoFonte)) erroArquivo(dir::CaminhoFonte.string());
    if (!icone.loadFromFile(dir::CaminhoIcone)) erroArquivo(dir::CaminhoIcone.string());
    janela.create(sf::VideoMode(recursoManagerPtr->getResolucaoSistema()), L"Invasores do Espaço", sf::Style::Close);
    janela.setFramerateLimit(recursoManagerPtr->getQps());
    janela.setIcon(icone);

    textoVidas.setString("Vidas: " + std::to_string(estadoJogadorPtr->getVidas()));
    textoVidas.setFillColor(sf::Color::White);
    textoVidas.setCharacterSize(static_cast<unsigned int>(recursoManagerPtr->getResolucaoSistema().x / 40));
    textoVidas.setPosition(sf::Vector2f({recursoManagerPtr->getResolucaoSistema().x*0.85f , 10.f}));

    textoPontos.setString("Pontos: " + std::to_string(estadoJogadorPtr->getPontos()));
    textoPontos.setFillColor(sf::Color::White);
    textoPontos.setCharacterSize(static_cast<unsigned int>(recursoManagerPtr->getResolucaoSistema().x / 40));
    textoPontos.setPosition(sf::Vector2f({recursoManagerPtr->getResolucaoSistema().x*0.01f , 10.f}));

    textoPerdeu.setFillColor(sf::Color::White);
    textoPerdeu.setCharacterSize(static_cast<unsigned int>(recursoManagerPtr->getResolucaoSistema().x / 40));
    textoPerdeu.setOrigin(textoPerdeu.getGlobalBounds().size / 2.f);
    textoPerdeu.setPosition(sf::Vector2f{recursoManagerPtr->getResolucaoSistema().x / 2.f, 10.f});

    relogio.start();
}

bool Interface::getEstado() const {
    return janela.isOpen();
}

void Interface::perdeuJogo() {
    textoPerdeu.setString(L"Você perdeu.\nPontuação total: " + std::to_wstring(estadoJogadorPtr->getPontos()) + L"\nPressione ENTER para recomeçar:");
}

void Interface::restaurar() {
    if(estadoJogadorPtr->getVidas() == 0) estadoJogadorPtr->setVidas(3);
    setPontuacao(Tipo::Reset);
    textoPerdeu.setString(L"");
    setTravar(0);
}

void Interface::setPontuacao(const Tipo tipo) {
    switch (tipo) {
        case Tipo::Circulo:
        estadoJogadorPtr->setPontos(estadoJogadorPtr->getPontos()+10);
        break;
        case Tipo::Quadrado:
        estadoJogadorPtr->setPontos(estadoJogadorPtr->getPontos()+20);
        break;
        case Tipo::Triangulo:
        estadoJogadorPtr->setPontos(estadoJogadorPtr->getPontos()+40);
        break;
        case Tipo::Reset:
        estadoJogadorPtr->setPontos(0);
        break;
    }
    textoPontos.setString("Pontos: " + std::to_string(estadoJogadorPtr->getPontos()));
    if(estadoJogadorPtr->getPontos() != 0 && estadoJogadorPtr->getPontos() % 1500 == 0 && estadoJogadorPtr->getVidas() < 3 && estadoJogadorPtr->getVidas() != 0) {
        estadoJogadorPtr->setVidas(estadoJogadorPtr->getVidas()+1);
    }
}

void Interface::updateVidas() {
    if(estadoJogadorPtr->getVidas() > 0) estadoJogadorPtr->setVidas(estadoJogadorPtr->getVidas()-1);
    textoVidas.setString("Vidas: " + std::to_string(estadoJogadorPtr->getVidas()));
}

void Interface::atualizarProjeteis() {
    gerenciadorProjeteisPtr->atualizarProjeteis();
}

void Interface::atualizarColisoes() {
    // Jogador acerta alguém
    for(auto &linhaAlien: gerenciadorAliensPtr->getGridAliens()) { {
        for(auto &alien: linhaAlien) {
            for(auto &it: gerenciadorProjeteisPtr->getBalasJogador())
                if(alien.checarColisao(it)) {
                    alien.morte();
                    it.setRemover(true);
                }
            }
        }
    }
    // Jogador é atingido
    /*
        iterar por cada bala e acionar morte e iniciar sistema de morte
    */
}

bool Interface::getTravar() const {
    return travar;
}

void Interface::setTravar(bool estado) {
    travar = estado;
}

void Interface::eventos() {
    janela.handleEvents(
        [this](const sf::Event::Closed) { janela.close(); },
        [this](const sf::Event::KeyPressed tecla) {
            if(tecla.scancode == sf::Keyboard::Scancode::Escape) janela.close();

            if(!travar) {
                if(tecla.scancode == sf::Keyboard::Scancode::Left) {
                    if(jogadorPtr->getSprite().getGlobalBounds().position.x > recursoManagerPtr->getLimitesTela()[Direcao::Esquerda]) {
                        jogadorPtr->mover(Direcao::Esquerda);
                    }
                }
                if(tecla.scancode == sf::Keyboard::Scancode::Right) {
                    if(jogadorPtr->getPosicao().x + jogadorPtr->getSprite().getGlobalBounds().size.x/2.f < recursoManagerPtr->getLimitesTela()[Direcao::Direita]){
                        jogadorPtr->mover(Direcao::Direita);
                    }
                }
                if(tecla.scancode == sf::Keyboard::Scancode::Space) {
                    gerenciadorProjeteisPtr->atirarJogador(jogadorPtr->getPosicao());
                }
            }
        }
    );
}

void Interface::desenhar() {
    janela.clear();
    if(relogio.getElapsedTime().asSeconds() > 1.f) {
        gerenciadorAliensPtr->moverGrid();
        relogio.restart();
    }
    janela.draw(textoVidas);
    janela.draw(textoPontos);
    janela.draw(jogadorPtr->getSprite());
    for(const auto &linhaAlien: gerenciadorAliensPtr->getGridAliens()) {
        for(const auto &alien: linhaAlien) {
            if(alien.getEstado() == Estado::Vivo) janela.draw(alien.getSprite());
        }

    }
    for(const auto &bala: gerenciadorProjeteisPtr->getBalasJogador()) janela.draw(bala.getForma());
    for(const auto &bala: gerenciadorProjeteisPtr->getBalasAlien()) janela.draw(bala.getSprite());
    janela.display();
}
