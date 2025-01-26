#include <gerenciadorInimigos.hpp>
#include <erroManuseio.hpp>
#include <vector>
#include <string>
#include <filesystem>
#include <enums.hpp>
#include <SFML/Graphics.hpp>

gerenciadorInimigos::gerenciadorInimigos(const std::filesystem::path &caminhoTextura, const sf::Vector2u &resolucaoSistema, const int qps, const std::vector<std::vector<alien>>& mapaTipos)
    : resolucaoSistema(resolucaoSistema), escala(resolucaoSistema.x/200.f), velocidade(static_cast<float>(resolucaoSistema.x/qps)), qps(qps), vertices(sf::PrimitiveType::Triangles) {
    if(!textura.loadFromFile(caminhoTextura)) erroArquivo(caminhoTextura.string());
    limites[enums::direcao::esquerda] = resolucaoSistema.x*0.1f;
    limites[enums::direcao::direita] = resolucaoSistema.x*0.9f;
    posicaoPrimeirox =  (resolucaoSistema.x - (11 * 16))/2.f;
    posicaoPrimeiroy =  resolucaoSistema.y*0.1f;

    const float larguraBaseInimigo = 16.f; // Largura base de um inimigo
    const float alturaBaseInimigo = 8.f;   // Altura base de um inimigo
    posicaoPrimeirox = (resolucaoSistema.x - (11 * larguraBaseInimigo * escala)) / 2.f;
    posicaoPrimeiroy = resolucaoSistema.y * 0.1f;

    for (int linha = 0; linha < 5; ++linha) {
        for (int coluna = 0; coluna < 11; ++coluna) {
            sf::Vector2f posicao(
                posicaoPrimeirox + coluna * larguraBaseInimigo * escala,
                posicaoPrimeiroy + linha * (alturaBaseInimigo * escala) + (linha != 0 ? linha * escala*2 : 0)
            );

            // Redimensione o VertexArray antes de acessar os vértices
            std::size_t index = vertices.getVertexCount();
            vertices.resize(index + 6); // 6 vértices = 2 triângulos

            // Acesse os vértices após o redimensionamento
            sf::Vertex* tri1 = &vertices[index];

            // Triângulo 1
            tri1[0].position = sf::Vector2f(posicao.x, posicao.y);
            tri1[1].position = sf::Vector2f(posicao.x + larguraBaseInimigo * escala, posicao.y);
            tri1[2].position = sf::Vector2f(posicao.x, posicao.y + alturaBaseInimigo * escala);

            // Triângulo 2
            tri1[3].position = sf::Vector2f(posicao.x + larguraBaseInimigo * escala, posicao.y);
            tri1[4].position = sf::Vector2f(posicao.x + larguraBaseInimigo * escala, posicao.y + alturaBaseInimigo * escala);
            tri1[5].position = sf::Vector2f(posicao.x, posicao.y + alturaBaseInimigo * escala);

            // Coordenadas de textura
            tri1[0].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[0].x, mapaTipos[linha][coluna].posSprites[0].y);
            tri1[1].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[0].x + larguraBaseInimigo, mapaTipos[linha][coluna].posSprites[0].y);
            tri1[2].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[0].x, mapaTipos[linha][coluna].posSprites[0].y + alturaBaseInimigo);

            tri1[3].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[0].x + larguraBaseInimigo, mapaTipos[linha][coluna].posSprites[0].y);
            tri1[4].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[0].x + larguraBaseInimigo, mapaTipos[linha][coluna].posSprites[0].y + alturaBaseInimigo);
            tri1[5].texCoords = sf::Vector2f(mapaTipos[linha][coluna].posSprites[0].x, mapaTipos[linha][coluna].posSprites[0].y + alturaBaseInimigo);
        }
    }
}

void gerenciadorInimigos::animar() {
    if(contador >= qps) {
        contador = 0;
        switch(direcao) {
            case enums::direcao::direita:
                for(int i = 0; i < 55; ++i) {
                    sf::Vertex* tri = &vertices[i];
                }
                break;
        }
    }
}

void gerenciadorInimigos::desenhar(sf::RenderWindow& janela) {
    janela.draw(vertices, &textura);
}