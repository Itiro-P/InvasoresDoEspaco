#include <gerenciadorInimigos.hpp>
#include <erroManuseio.hpp>
#include <vector>
#include <string>
#include <filesystem>
#include <enums.hpp>
#include <SFML/Graphics.hpp>

gerenciadorInimigos::gerenciadorInimigos(const std::filesystem::path &caminhoTextura, const sf::Vector2u &resolucaoSistema, const int qps, const std::array<std::array<alien, 11>, 5> &mapaTipos)
    : resolucaoSistema(resolucaoSistema), escala(resolucaoSistema.x / 200.f), velocidade(static_cast<float>(resolucaoSistema.x / qps)), qps(qps), mapaTipos(mapaTipos)
{
    if(!textura.loadFromFile(caminhoTextura)) erroArquivo(caminhoTextura.string());
    limites[enums::direcao::esquerda] = resolucaoSistema.x*0.05f;
    limites[enums::direcao::direita] = resolucaoSistema.x*0.95f;

    posTopoEsquerdoX = (resolucaoSistema.x - (11 * tamanhoSpriteX * escala)) / 2.f;
    posTopoEsquerdoY = resolucaoSistema.y / 10.f;

    for (auto &linha : vertices) {
        linha.setPrimitiveType(sf::PrimitiveType::Triangles);
        linha.resize(11 * 6); // Cada linha contém 11 sprites, cada sprite com 6 vértices
    }

    for (int linha = 0; linha < 5; ++linha) {
        for (int coluna = 0; coluna < 11; ++coluna) {
            sf::Vertex *tri1 = &vertices[linha][coluna * 6];
            sf::Vector2f posicao(
                posTopoEsquerdoX + coluna * tamanhoSpriteX * escala,
                posTopoEsquerdoY + linha * tamanhoSpriteY * escala + (linha != 0 ? linha * escala * 2.f : 0.f));

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

void gerenciadorInimigos::atualizarVertices() {
    if (contador >= qps) {
        contador = 0;
        spriteAtual = (spriteAtual == 0 ? 1 : 0);

        switch (direcao) {
        case enums::direcao::direita:
            if (vertices[0].getBounds().position.x + vertices[0].getBounds().size.x <= limites[enums::direcao::direita]) {
                for (int linha = 0; linha < 5; ++linha) {
                    for (int coluna = 0; coluna < 11; ++coluna) {
                        sf::Vertex* tri1 = &vertices[linha][coluna * 6];
                        tri1[0].position.x += velocidade;
                        tri1[1].position.x += velocidade;
                        tri1[2].position.x += velocidade;
                        tri1[3].position.x += velocidade;
                        tri1[4].position.x += velocidade;
                        tri1[5].position.x += velocidade;

                        atualizarSprites(tri1, linha, coluna);
                    }
                }
            } else {
                direcao = enums::direcao::esquerda;
                for (int linha = 0; linha < 5; ++linha) {
                    for (int coluna = 0; coluna < 11; ++coluna) {
                        sf::Vertex* tri1 = &vertices[linha][coluna * 6];
                        tri1[0].position.y += velocidade * 0.5f;
                        tri1[1].position.y += velocidade * 0.5f;
                        tri1[2].position.y += velocidade * 0.5f;
                        tri1[3].position.y += velocidade * 0.5f;
                        tri1[4].position.y += velocidade * 0.5f;
                        tri1[5].position.y += velocidade * 0.5f;

                        atualizarSprites(tri1, linha, coluna);
                    }
                }
            }
            break;

        case enums::direcao::esquerda:
            if (vertices[0][0].position.x >= limites[enums::direcao::esquerda]) {
                for (int linha = 0; linha < 5; ++linha) {
                    for (int coluna = 0; coluna < 11; ++coluna) {
                        sf::Vertex* tri1 = &vertices[linha][coluna * 6];
                        tri1[0].position.x -= velocidade;
                        tri1[1].position.x -= velocidade;
                        tri1[2].position.x -= velocidade;
                        tri1[3].position.x -= velocidade;
                        tri1[4].position.x -= velocidade;
                        tri1[5].position.x -= velocidade;

                        atualizarSprites(tri1, linha, coluna);
                    }
                }
            } else {
                direcao = enums::direcao::direita;
                for (int linha = 0; linha < 5; ++linha) {
                    for (int coluna = 0; coluna < 11; ++coluna) {
                        sf::Vertex* tri1 = &vertices[linha][coluna * 6];
                        tri1[0].position.y += velocidade * 0.5f;
                        tri1[1].position.y += velocidade * 0.5f;
                        tri1[2].position.y += velocidade * 0.5f;
                        tri1[3].position.y += velocidade * 0.5f;
                        tri1[4].position.y += velocidade * 0.5f;
                        tri1[5].position.y += velocidade * 0.5f;

                        atualizarSprites(tri1, linha, coluna);
                    }
                }
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

alien gerenciadorInimigos::getAlien(const int linha, const int coluna) const & {
    return mapaTipos[linha][coluna];
}

void gerenciadorInimigos::atualizarSprites(sf::Vertex* vertice, const int linha, const int coluna) {
    vertice[0].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[spriteAtual].x, mapaTipos[linha][coluna].posSprites[spriteAtual].y);
    vertice[1].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[spriteAtual].x + tamanhoSpriteX, mapaTipos[linha][coluna].posSprites[spriteAtual].y);
    vertice[2].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[spriteAtual].x, mapaTipos[linha][coluna].posSprites[spriteAtual].y + tamanhoSpriteY);
    vertice[3].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[spriteAtual].x + tamanhoSpriteX, mapaTipos[linha][coluna].posSprites[spriteAtual].y);
    vertice[4].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[spriteAtual].x + tamanhoSpriteX, mapaTipos[linha][coluna].posSprites[spriteAtual].y + tamanhoSpriteY);
    vertice[5].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[spriteAtual].x, mapaTipos[linha][coluna].posSprites[spriteAtual].y + tamanhoSpriteY);
}