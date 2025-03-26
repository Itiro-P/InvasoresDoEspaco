#include <gerenciadorAliens.hpp>
#include <erroManuseio.hpp>
#include <string>
#include <filesystem>
#include <interface.hpp>
#include <random>

GerenciadorAliens::GerenciadorAliens(RecursoManager &recursoManager) : recursoManagerPtr(std::make_shared<RecursoManager>(recursoManager)) {
    velocidade = static_cast<float>(recursoManagerPtr->getResolucaoSistema().x/recursoManagerPtr->getQps());
    for(int linha = 0; linha < 5; ++linha) {
        for(int coluna = 0; coluna < 11; ++coluna) {
            float posicaoX = recursoManagerPtr->getLimitesTela()[Direcao::Esquerda] + gridAliens[linha][coluna].getSprite().getGlobalBounds().size.x/2.f + gridAliens[linha][coluna].getSprite().getGlobalBounds().size.x*coluna;
            float posicaoY = recursoManagerPtr->getResolucaoSistema().x/10.f + gridAliens[linha][coluna].getSprite().getGlobalBounds().size.y*linha + recursoManagerPtr->getEscala()*linha;
            sf::Vector2f posicao{posicaoX, posicaoY};
            gridAliens[linha][coluna].setPosicao(posicao);
        }
    }
    posTopoEsquerdoX = gridAliens.front().front().getPosicao().x;
    posTopoEsquerdoY = gridAliens.front().front().getPosicao().y;
}

void GerenciadorAliens::moverGrid()
{
    if (gridAliens.empty() || gridAliens[0].empty()) { return; }
        
    bool atingiuLimite = false;
    
    if (direcao == Direcao::Direita) {
        atingiuLimite = (posTopoEsquerdoX + recursoManagerPtr->getTamanhoSprite().x * 10 * recursoManagerPtr->getEscala() >= recursoManagerPtr->getLimitesTela()[Direcao::Direita]);
    } else {
        atingiuLimite = (posTopoEsquerdoX <= recursoManagerPtr->getLimitesTela()[Direcao::Esquerda]);
    }
        
    sf::Vector2f deslocamento;
        
    if (atingiuLimite) {
        deslocamento = sf::Vector2f{0.f, velocidade / 2.f};
        posTopoEsquerdoY += velocidade / 2.f;
        direcao = (direcao == Direcao::Direita) ? Direcao::Esquerda : Direcao::Direita;
    } else {
        deslocamento = (direcao == Direcao::Direita) ? sf::Vector2f{velocidade, 0.f} : sf::Vector2f{-velocidade, 0.f};
        posTopoEsquerdoX += (direcao == Direcao::Direita) ? velocidade : -velocidade;
    }
    spriteAtual = (spriteAtual == 1 ? 0 : 1);
    for (auto& linha : gridAliens) {
        for (auto& alien : linha) {
            if (alien.getEstado() == Estado::Vivo) {
                alien.mover(deslocamento);
                alien.setSpriteAtual(recursoManagerPtr->getPosSpritesAliens()[alien.getTipo()][spriteAtual]);
            }
            else if(alien.getEstado() == Estado::Morrendo) {
                alien.setSpriteAtual(recursoManagerPtr->getPosSpritesAliens()[alien.getTipo()][2]);
                alien.setEstado(Estado::Morto);
                --aliensVivos;
            }
        }
    }
}


void GerenciadorAliens::restaurarGrid() {
    contadorBalas = 0;
    direcao = Direcao::Esquerda;
    aliensVivos = 55;
    spriteAtual = 0;
    for(int linha = 0; linha < 5; ++linha) {
        for(int coluna = 0; coluna < 11; ++coluna) {
            sf::Vector2f posicao{recursoManagerPtr->getResolucaoSistema().x*0.05f + recursoManagerPtr->getTamanhoSprite().x*coluna*recursoManagerPtr->getEscala(), recursoManagerPtr->getResolucaoSistema().x/10.f + recursoManagerPtr->getTamanhoSprite().y*linha*recursoManagerPtr->getEscala() + recursoManagerPtr->getEscala()*linha};
            gridAliens[linha][coluna].setPosicao(posicao);
            gridAliens[linha][coluna].setEstado(Estado::Vivo);
            gridAliens[linha][coluna].setSpriteAtual(recursoManagerPtr->getPosSpritesAliens()[gridAliens[linha][coluna].getTipo()][spriteAtual]);
        }
    }
    posTopoEsquerdoX = gridAliens.front().front().getPosicao().x;
    posTopoEsquerdoY = gridAliens.front().front().getPosicao().y;
}

/*
void GerenciadorAliens::atirar() {
    if (aliensVivos == 0) return;

    // Contador para controlar a frequência de tiros (ex: 1 tiro por segundo)
    contadorBalas++;
    if (contadorBalas < recursoManagerPtr->getQps()) return; // Ajuste "qps" conforme necessário
    contadorBalas = 0;

    // Lista de inimigos vivos
    std::vector<std::pair<int, int>> inimigosVivosPosicoes;
    for (int linha = 0; linha < 5; ++linha) {
        for (int coluna = 0; coluna < 11; ++coluna) {
            if (gridAliens[linha][coluna].getEstado() == Estado::Vivo) {
                inimigosVivosPosicoes.emplace_back(linha, coluna);
            }
        }
    }

    // Não atirar se não houver inimigos vivos
    if (inimigosVivosPosicoes.empty()) return;

    // Selecionar um inimigo vivo aleatório
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> distrib(0, inimigosVivosPosicoes.size() - 1);
    int idx = distrib(gen);
    auto [linha, coluna] = inimigosVivosPosicoes[idx];

    // Posição da bala
    sf::Vector2f posicaoInimigo = gridAliens[linha][coluna].getPosicao();
    sf::Vector2f posicaoBala = posicaoInimigo + sf::Vector2f{
        recursoManagerPtr->getTamanhoSprite().x * recursoManagerPtr->getEscala() / 2.f,
        recursoManagerPtr->getTamanhoSprite().y * recursoManagerPtr->getEscala()
    };

    balasAlien.emplace_back(gridAliens[linha][coluna].getTipo(), recursoManagerPtr->getPosSpritesAliens()[gridAliens[linha][coluna].getTipo()], TexturaManager::getTextura(dir::CaminhoSprites), posicaoBala, recursoManagerPtr->getVelocidadeBalas(), recursoManagerPtr->getEscala());
}
*/