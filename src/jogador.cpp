#include <jogador.hpp>
#include <erroManuseio.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <janela.hpp>
#include <enums.hpp>
#include <GerenciadorInimigos.hpp>
#include <string>

Jogador::Jogador(const sf::Vector2u& resolucaoSistema, const std::filesystem::path& caminhoTextura, const int quantidadeSprites, const std::vector<sf::IntRect>& posSprites, const sf::Vector2f& tamanhoSprite, const int qps)
: resolucaoSistema(resolucaoSistema), quantidadeSprites(quantidadeSprites), posSprites(posSprites), sprite(textura), tamanhoSprite(tamanhoSprite), escala(resolucaoSistema.x/200.f), qps(qps) {
    limites[Direcao::Esquerda] = resolucaoSistema.x*0.05f;
    limites[Direcao::Direita] = resolucaoSistema.x*0.95f;
    velocidade = static_cast<float>(resolucaoSistema.x/qps);
    if(!textura.loadFromFile(caminhoTextura)) erroArquivo(caminhoTextura.string());
    sprite.setTexture(textura);
    sprite.setTextureRect(posSprites[0]);
    sprite.setOrigin(sf::Vector2f({tamanhoSprite.x/2.f, tamanhoSprite.y/2.f}));
    sprite.setPosition(sf::Vector2f({ resolucaoSistema.x/2.f - escala, resolucaoSistema.y*0.9f }));
    sprite.setScale(sf::Vector2f({escala, escala}));

    balaCooldown.start();
}

void Jogador::atualizarBalas() {
    for(auto& bala: balas) {
        bala.mover();
    }
}

void Jogador::mover(const Direcao dir) {
    switch(dir) {
        case Direcao::Direita:
            if(sprite.getPosition().x < limites[Direcao::Direita]) sprite.move(sf::Vector2f({velocidade, 0.f}));
            break;
        case Direcao::Esquerda:
            if(sprite.getPosition().x > limites[Direcao::Esquerda]) sprite.move(sf::Vector2f({-velocidade, 0.f}));
            break;
    }
}

void Jogador::atirar() {
    if(balaCooldown.getElapsedTime().asSeconds() > 0.5f) {
        balaCooldown.restart();
        balas.emplace_back(sprite.getPosition(), escala, qps);
    }
}

void Jogador::morte(Janela& janela) {
    janela.setTravar(1);
    janela.updateVidas();
    animando = true;
    contador = 0;
    contador2 = 0;
    spriteAtual = 1;
    sprite.setTextureRect(posSprites[spriteAtual]);
}

void Jogador::calcularColisao(GerenciadorInimigos& GerenciadorInimigos, Janela& janela) {
    auto it = balas.begin();
    while (it != balas.end()) {
        bool colisaoDetectada = false;

        for (int linha = 4; linha >= 0; --linha) {
            for (int coluna = 0; coluna < 11; ++coluna) {
                auto& inimigo = GerenciadorInimigos.getMapa()[linha][coluna];


                // Verifica se o inimigo está vivo
                if (inimigo.getEstado() == Condicao::Vivo) {

                    // Verifica colisão
                    if (inimigo.checarColisao(*it)) {
                        inimigo.setEstado(Condicao::Morrendo);
                        inimigo.setRect(2);
                        janela.setPontuacao(inimigo.getTipo());
                        colisaoDetectada = true;
                        break; // Sai do loop de colisão
                    }
                }
            }
            if (colisaoDetectada) break; // Sai do loop de linhas
        }

        // Remove a bala se houve colisão
        if (colisaoDetectada) {
            it = balas.erase(it);
        } else {
            ++it;
        }
    }
}

void Jogador::atualizarAnimacaoMorte(Janela& janela) {
    if (!animando) return;

    if(contador >= qps/4 && contador2 < qps*2) {
        ++contador2;
        contador = 0;
        spriteAtual = (spriteAtual == 1 ? 2 : 1);
        sprite.setTextureRect(posSprites[spriteAtual]);
    } else {
        ++contador2;
        ++contador;
    }
}

void Jogador::restaurarJogador() {
    sprite.setPosition(sf::Vector2f({ resolucaoSistema.x/2.f - escala, resolucaoSistema.y*0.9f }));
    animando = 0;
    sprite.setTextureRect(posSprites[0]);
    balas.clear();
}

std::vector<Bala> Jogador::getBalas() const {
    return balas;
}

sf::Vector2f Jogador::getPosition() const {
    return sprite.getPosition();
}

sf::Sprite Jogador::getSprite() const {
    return sprite;
}


void Jogador::removerBalasForaDaTela() {
    auto it = balas.begin();
    while (it != balas.end()) {
        if (it->getPosition().y + it->getRectBala().size.y < 0.f ) {
            it = balas.erase(it);
        } else {
            ++it;
        }
    }
}


Bala::Bala(const sf::Vector2f &posicao, const float escala, const int qps) : posicao(posicao), escala(escala), qps(qps) {
    velocidade = -qps/15.f;
    forma.setPosition(sf::Vector2f(posicao.x, posicao.y*0.9f));
    forma.setSize(sf::Vector2f(1.f * escala, 4.f * escala));
}

sf::FloatRect Bala::getRectBala() const {
    return sf::FloatRect(forma.getPosition(), forma.getSize());
}

sf::RectangleShape Bala::getForma() const {
    return forma;
}

sf::Vector2f Bala::getPosition() const {
    return forma.getPosition();
}


void Bala::mover() {
    forma.move(sf::Vector2f(0.f, velocidade));
}
