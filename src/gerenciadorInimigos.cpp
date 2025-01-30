#include <gerenciadorInimigos.hpp>
#include <erroManuseio.hpp>
#include <vector>
#include <string>
#include <filesystem>
#include <enums.hpp>
#include <SFML/Graphics.hpp>

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
                }
            }
        }
    } else {
        ++contadorQuadros;
    }
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
