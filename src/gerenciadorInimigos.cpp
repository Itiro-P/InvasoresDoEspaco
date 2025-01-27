#include <gerenciadorInimigos.hpp>
#include <erroManuseio.hpp>
#include <vector>
#include <string>
#include <filesystem>
#include <enums.hpp>
#include <SFML/Graphics.hpp>

gerenciadorInimigos::gerenciadorInimigos(const std::filesystem::path &caminhoTextura, const sf::Vector2u &resolucaoSistema, const int qps, const std::array<std::array<alien, 11>, 5>& mapaTipos)
    : resolucaoSistema(resolucaoSistema), escala(resolucaoSistema.x/200.f), velocidade(static_cast<float>(resolucaoSistema.x/qps)), qps(qps), mapaTipos(mapaTipos) {
    if(!textura.loadFromFile(caminhoTextura)) erroArquivo(caminhoTextura.string());
    limites[enums::direcao::esquerda] = resolucaoSistema.x*0.05f;
    limites[enums::direcao::direita] = resolucaoSistema.x*0.95f;
    posTopoEsquerdoX = (resolucaoSistema.x - (11 * 16))/2.f;
    posTopoEsquerdoY = resolucaoSistema.y/10.f;
    for(auto& linha: vertices) {
        linha.setPrimitiveType(sf::PrimitiveType::Triangles);
        linha.resize(66);
    }
    for(int linha = 0; linha < 5; ++linha) {
        for(int coluna = 0; coluna < 11; ++coluna) {
            sf::Vertex* tri1 = &vertices[linha][coluna];
            sf::Vector2f posicao(
                posTopoEsquerdoX + tamanhoSpriteX*coluna,
                posTopoEsquerdoY + tamanhoSpriteY*linha + (linha != 0 ? linha*escala*2.f: 0.f)
            );
            tri1[0].position = sf::Vector2f(posicao.x, posicao.y);
            tri1[1].position = sf::Vector2f(posicao.x + tamanhoSpriteX * escala, posicao.y);
            tri1[2].position = sf::Vector2f(posicao.x, posicao.y + tamanhoSpriteY * escala);

            tri1[3].position = sf::Vector2f(posicao.x + tamanhoSpriteX * escala, posicao.y);
            tri1[4].position = sf::Vector2f(posicao.x + tamanhoSpriteX * escala, posicao.y + tamanhoSpriteY * escala);
            tri1[5].position = sf::Vector2f(posicao.x, posicao.y + tamanhoSpriteY * escala);

            tri1[0].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[spriteAtual].x, mapaTipos[linha][coluna].posSprites[spriteAtual].y);
            tri1[1].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[spriteAtual].x + tamanhoSpriteX, mapaTipos[linha][coluna].posSprites[spriteAtual].y);
            tri1[2].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[spriteAtual].x, mapaTipos[linha][coluna].posSprites[spriteAtual].y + tamanhoSpriteY);

            tri1[3].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[spriteAtual].x + tamanhoSpriteX, mapaTipos[linha][coluna].posSprites[spriteAtual].y);
            tri1[4].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[spriteAtual].x + tamanhoSpriteX, mapaTipos[linha][coluna].posSprites[spriteAtual].y + tamanhoSpriteY);
            tri1[5].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[spriteAtual].x, mapaTipos[linha][coluna].posSprites[spriteAtual].y + tamanhoSpriteY);
        }
    }
}
void gerenciadorInimigos::animar() {
    if(contador >= qps) {
        contador = 0;
        spriteAtual = (spriteAtual == 0 ? 1 : 0);
        switch(direcao) {
        case enums::direcao::direita:
            if(vertices[0].getBounds().position.x + vertices[0].getBounds().size.x <= limites[enums::direcao::direita]) {
                for(int linha = 0; linha < 5; ++linha) {
                    for(int coluna = 0; coluna < 11; ++coluna) {
                        vertices[linha][coluna].position.x += velocidade;
                        vertices[linha][coluna].texCoords = mapaTipos[linha][coluna].posSprites[spriteAtual];
                    }
                }
            }
            else {
               for(int linha = 0; linha < 5; ++linha) {
                    for(int coluna = 0; coluna < 11; ++coluna) {
                        vertices[linha][coluna].position.y += velocidade;
                        vertices[linha][coluna].texCoords = mapaTipos[linha][coluna].posSprites[spriteAtual];
                    }
                }
                direcao = enums::direcao::esquerda;
            }
            break;
        case enums::direcao::esquerda:
            if(vertices[0].getBounds().position.x + vertices[0].getBounds().size.x >= limites[enums::direcao::direita]) {
                for(int linha = 0; linha < 5; ++linha) {
                    for(int coluna = 0; coluna < 11; ++coluna) {
                        vertices[linha][coluna].position.x -= velocidade;
                        vertices[linha][coluna].texCoords = mapaTipos[linha][coluna].posSprites[spriteAtual];
                    }
                }
            }
            else {
               for(int linha = 0; linha < 5; ++linha) {
                    for(int coluna = 0; coluna < 11; ++coluna) {
                        vertices[linha][coluna].position.y += velocidade;
                        vertices[linha][coluna].texCoords = mapaTipos[linha][coluna].posSprites[spriteAtual];
                    }
                }
                direcao = enums::direcao::direita;
            }
            break;
        }
    }
    else ++contador;
}

void gerenciadorInimigos::desenhar(sf::RenderWindow& janela) {
    for(auto& linha : vertices) {
        janela.draw(linha, &textura);
    }
}