#include <gerenciadorInimigos.hpp>
#include <erroManuseio.hpp>
#include <vector>
#include <string>
#include <filesystem>
#include <enums.hpp>
#include <SFML/Graphics.hpp>
#include <jogador.hpp>
#include <janela.hpp>
#include <random>

gerenciadorInimigos::gerenciadorInimigos(const std::filesystem::path &caminhoTextura, const sf::Vector2u &resolucaoSistema, const int qps, const std::array<std::array<alien, 11>, 5>& mapaInimigos)
: resolucaoSistema(resolucaoSistema), qps(qps), mapa(mapaInimigos) {
    if(!textura.loadFromFile(caminhoTextura)) erroArquivo(caminhoTextura.string());
    escala = resolucaoSistema.x/200.f;
    velocidade = static_cast<float>(resolucaoSistema.x/qps);
    limites[enums::direcao::esquerda] = resolucaoSistema.x*0.03f;
    limites[enums::direcao::direita] = resolucaoSistema.x*0.9f;
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

void gerenciadorInimigos::atualizarPosicao() {
    if (contadorQuadros >= qps) {
        contadorQuadros = 0;
        
        if (mapa.empty() || mapa[0].empty()) {
            return;
        }
        
        bool atingiuLimite = false;
    
        if (direcao == enums::direcao::direita) {
            atingiuLimite = (posTopoEsquerdoX + tamanhoSprite.x * 10 * escala >= limites[enums::direcao::direita]);
        } else {
            atingiuLimite = (posTopoEsquerdoX <= limites[enums::direcao::esquerda]);
        }
        
        sf::Vector2f movimento;
        
        if (atingiuLimite) {
            movimento = sf::Vector2f{0.f, velocidade / 2.f};
            posTopoEsquerdoY += velocidade / 2.f;
            direcao = (direcao == enums::direcao::direita) ? enums::direcao::esquerda : enums::direcao::direita;
        } else {
            movimento = (direcao == enums::direcao::direita) ? sf::Vector2f{velocidade, 0.f} : sf::Vector2f{-velocidade, 0.f};
            posTopoEsquerdoX += (direcao == enums::direcao::direita) ? velocidade : -velocidade;
        }
        spriteAtual = (spriteAtual == 1 ? 0 : 1);
        for (auto& linha : mapa) {
            for (auto& inimigo : linha) {
                if (inimigo.getEstado() == enums::condicao::vivo) {
                    inimigo.inimigoMover(movimento);
                    inimigo.setRect(spriteAtual);
                }
                else if(inimigo.getEstado() == enums::condicao::morrendo) {
                    inimigo.setRect(spriteMorte);
                    inimigo.setEstado(enums::condicao::morto);
                    --inimigosVivos;
                }
            }
        }
    } else {
        ++contadorQuadros;
    }
}

void gerenciadorInimigos::atualizarBalas() {
    for(auto& bala : balasInimigo) bala.mover();
}

void gerenciadorInimigos::restaurarPosicoes() {
    inimigosVivos = 55;
    spriteAtual = 0;
    for(int linha = 0; linha < 5; ++linha) {
        for(int coluna = 0; coluna < 11; ++coluna) {
            sf::Vector2f posicao{resolucaoSistema.x*0.05f + tamanhoSprite.x*coluna*escala, resolucaoSistema.x/10.f + tamanhoSprite.y*linha*escala + escala*linha};
            mapa[linha][coluna].setPosition(posicao);
            mapa[linha][coluna].setEstado(enums::condicao::vivo);
            mapa[linha][coluna].setRect(spriteAtual);
        }
    }
    posTopoEsquerdoX = mapa.front().front().getPosition().x;
    posTopoEsquerdoY = mapa.front().front().getPosition().y;
}

void gerenciadorInimigos::atirar() {
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
        } while (mapa[linha][coluna].getEstado() != enums::condicao::vivo);

        sf::Vector2f posicaoInimigo = mapa[linha][coluna].getPosition();
        sf::Vector2f posicaoBala = posicaoInimigo + sf::Vector2f{tamanhoSprite.x * escala / 2.f, tamanhoSprite.y * escala};

        balasInimigo.emplace_back(posicaoBala, escala, qps, textura, mapa[linha][coluna].getPosSpritesBalas());
    }
    else ++contadorBalas;
}

void gerenciadorInimigos::calcularColisaoBalaInimigo(jogador& jogador, janela& janela) {
    auto it = balasInimigo.begin();
    while(it != balasInimigo.end()) {
        if(it->getPosition().y > resolucaoSistema.y) {
            it = balasInimigo.erase(it);
        } else {
            bool colisaoX = it->getPosition().x > jogador.getPosition().y && jogador.getPosition().x < jogador.getPosition().x + jogador.getSprite().getGlobalBounds().size.x;
            bool colisaoY = it->getPosition().y < jogador.getPosition().y && jogador.getPosition().y > jogador.getPosition().y - jogador.getSprite().getGlobalBounds().size.y;
            if(colisaoX && colisaoY) {
                it = balasInimigo.erase(it);
                jogador.morte(janela);
            }
        }
        ++it;
    }
}

int gerenciadorInimigos::getInimigosVivos() const &
{
    return inimigosVivos;
}

std::array<std::array<alien, 11>, 5>& gerenciadorInimigos::getMapa() {
    return mapa;
}

void gerenciadorInimigos::desenhar(sf::RenderWindow& janela) {
    for(const auto& linha : mapa) {
        for(const auto& inimigo : linha) {
            if(inimigo.getEstado() != enums::condicao::morto) janela.draw(inimigo.getSprite());
        }
    }
}

balaInimigo::balaInimigo(const sf::Vector2f &posicao, const float escala, const int qps, const sf::Texture& textura, const std::array<sf::IntRect, 4> &posSprites) : escala(escala) , qps(qps), textura(textura), sprite(textura) , posSprites(posSprites) {
    sprite.setTexture(textura);
    sprite.setTextureRect(posSprites[0]);
    sprite.setPosition(posicao);
    sprite.setScale(sf::Vector2f{escala, escala});
    velocidade = qps/15.f;
}

sf::Sprite balaInimigo::getSprite() const& {
    return sprite;
}

sf::Vector2f balaInimigo::getPosition() const& {
    return sprite.getPosition();
}

void balaInimigo::mover() {
    if(spriteAtual == 3) spriteAtual = 0;
    else ++spriteAtual;
    sprite.move(sf::Vector2f{0.f, velocidade});
    sprite.setTextureRect(posSprites[spriteAtual]);
}