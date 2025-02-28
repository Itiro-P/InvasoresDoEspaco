#include <GerenciadorInimigos.hpp>
#include <erroManuseio.hpp>
#include <vector>
#include <string>
#include <filesystem>
#include <enums.hpp>
#include <SFML/Graphics.hpp>
#include <jogador.hpp>
#include <janela.hpp>
#include <random>

GerenciadorInimigos::GerenciadorInimigos(const std::filesystem::path &caminhoTextura, const sf::Vector2u &resolucaoSistema, const int qps, const std::array<std::array<Alien, 11>, 5>& mapaInimigos)
: resolucaoSistema(resolucaoSistema), qps(qps), mapa(mapaInimigos) {
    if(!textura.loadFromFile(caminhoTextura)) erroArquivo(caminhoTextura.string());
    escala = resolucaoSistema.x/200.f;
    velocidade = static_cast<float>(resolucaoSistema.x/qps);
    limites[Direcao::Esquerda] = resolucaoSistema.x*0.03f;
    limites[Direcao::Direita] = resolucaoSistema.x*0.9f;
    escala = resolucaoSistema.x/200.f;
    for(int linha = 0; linha < 5; ++linha) {
        for(int coluna = 0; coluna < 11; ++coluna) {
            sf::Vector2f posicao{resolucaoSistema.x*0.05f + tamanhoSprite.x*coluna*escala, resolucaoSistema.x/10.f + tamanhoSprite.y*linha*escala + escala*linha};
            mapa[linha][coluna].setPosition(posicao);
            mapa[linha][coluna].setScale(sf::Vector2f{escala, escala});
        }
    }
    posTopoEsquerdoX = mapa.front().front().getPosition().x;
    posTopoEsquerdoY = mapa.front().front().getPosition().y;
}

void GerenciadorInimigos::atualizarPosicao() {
    if (contadorQuadros >= qps) {
        contadorQuadros = 0;
        
        if (mapa.empty() || mapa[0].empty()) {
            return;
        }
        
        bool atingiuLimite = false;
    
        if (direcao == Direcao::Direita) {
            atingiuLimite = (posTopoEsquerdoX + tamanhoSprite.x * 10 * escala >= limites[Direcao::Direita]);
        } else {
            atingiuLimite = (posTopoEsquerdoX <= limites[Direcao::Esquerda]);
        }
        
        sf::Vector2f movimento;
        
        if (atingiuLimite) {
            movimento = sf::Vector2f{0.f, velocidade / 2.f};
            posTopoEsquerdoY += velocidade / 2.f;
            direcao = (direcao == Direcao::Direita) ? Direcao::Esquerda : Direcao::Direita;
        } else {
            movimento = (direcao == Direcao::Direita) ? sf::Vector2f{velocidade, 0.f} : sf::Vector2f{-velocidade, 0.f};
            posTopoEsquerdoX += (direcao == Direcao::Direita) ? velocidade : -velocidade;
        }
        spriteAtual = (spriteAtual == 1 ? 0 : 1);
        for (auto& linha : mapa) {
            for (auto& inimigo : linha) {
                if (inimigo.getEstado() == Condicao::Vivo) {
                    inimigo.inimigoMover(movimento);
                    inimigo.setRect(spriteAtual);
                }
                else if(inimigo.getEstado() == Condicao::Morrendo) {
                    inimigo.setRect(spriteMorte);
                    inimigo.setEstado(Condicao::Morto);
                    --inimigosVivos;
                }
            }
        }
    } else {
        ++contadorQuadros;
    }
}

void GerenciadorInimigos::atualizarBalas() {
    for(auto& bala : balasInimigo) bala.mover();
}

void GerenciadorInimigos::restaurarPosicoes() {
    inimigosVivos = 55;
    spriteAtual = 0;
    balasInimigo.clear();
    for(int linha = 0; linha < 5; ++linha) {
        for(int coluna = 0; coluna < 11; ++coluna) {
            sf::Vector2f posicao{resolucaoSistema.x*0.05f + tamanhoSprite.x*coluna*escala, resolucaoSistema.x/10.f + tamanhoSprite.y*linha*escala + escala*linha};
            mapa[linha][coluna].setPosition(posicao);
            mapa[linha][coluna].setEstado(Condicao::Vivo);
            mapa[linha][coluna].setRect(spriteAtual);
        }
    }
    posTopoEsquerdoX = mapa.front().front().getPosition().x;
    posTopoEsquerdoY = mapa.front().front().getPosition().y;
}

void GerenciadorInimigos::atirar() {
    if(inimigosVivos == 0) return;

    if(contadorBalas >= qps) {
        contadorBalas = 0;
        std::random_device seed;
        std::mt19937 gen(seed());
        std::uniform_int_distribution<> distribLinha(0, 4);  // Linhas de 0 a 4
        std::uniform_int_distribution<> distribColuna(0, 10); // Colunas de 0 a 10
        int linha, coluna;
        do {
            linha = distribLinha(gen);
            coluna = distribColuna(gen);
        } while (mapa[linha][coluna].getEstado() != Condicao::Vivo);

        sf::Vector2f posicaoInimigo = mapa[linha][coluna].getPosition();
        sf::Vector2f posicaoBala = posicaoInimigo + sf::Vector2f{tamanhoSprite.x * escala / 2.f, tamanhoSprite.y * escala};

        balasInimigo.emplace_back(posicaoBala, escala, qps, textura, mapa[linha][coluna].getPosSpritesBalas());
    }
    else ++contadorBalas;
}

void GerenciadorInimigos::calcularColisaoBalaInimigo(Jogador& jogador, Janela& janela) {
    auto it = balasInimigo.begin();
    while (it != balasInimigo.end()) {

        if (it->getPosition().y > resolucaoSistema.y) {
            it = balasInimigo.erase(it);
            continue;
        }

        if (jogador.getSprite().getGlobalBounds().contains(it->getPosition())) {
            it = balasInimigo.erase(it);
            jogador.morte(janela);
            continue;
        }

        ++it;
    }
}

int GerenciadorInimigos::getInimigosVivos() const {
    return inimigosVivos;
}

std::array<std::array<Alien, 11>, 5>& GerenciadorInimigos::getMapa() {
    return mapa;
}

void GerenciadorInimigos::desenhar(sf::RenderWindow& janela) {
    for(const auto& linha : mapa) {
        for(const auto& inimigo : linha) {
            if(inimigo.getEstado() != Condicao::Morto) janela.draw(inimigo.getSprite());
        }
    }
    for(const auto& bala: balasInimigo) {
        janela.draw(bala.getSprite());
    }
}

BalaInimigo::BalaInimigo(const sf::Vector2f &posicao, const float escala, const int qps, const sf::Texture& textura, const std::array<sf::IntRect, 4> &posSprites) : escala(escala) , qps(qps), textura(textura), sprite(textura), posSprites(posSprites) {
    sprite.setTextureRect(posSprites[0]);
    sprite.setPosition(posicao);
    sprite.setScale(sf::Vector2f{escala, escala});
    velocidade = qps/15.f;
    cooldownQuadros = qps/5;
}

sf::Sprite BalaInimigo::getSprite() const {
    return sprite;
}

sf::Vector2f BalaInimigo::getPosition() const {
    return sprite.getPosition();
}

void BalaInimigo::mover() {
    if(contadorQuadros >= cooldownQuadros) {
        contadorQuadros = 0;
        if(spriteAtual == 3) spriteAtual = 0;
        else ++spriteAtual;

        sprite.setTextureRect(posSprites[spriteAtual]);
    }
    else ++contadorQuadros;
    sprite.move(sf::Vector2f{0.f, velocidade});
}