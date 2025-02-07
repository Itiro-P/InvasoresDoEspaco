#include <jogador.hpp>
#include <erroManuseio.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <janela.hpp>
#include <enums.hpp>
#include <gerenciadorInimigos.hpp>
#include <string>

jogador::jogador(const sf::Vector2u& resolucaoSistema, const std::filesystem::path& caminhoTextura, const int quantidadeSprites, const std::vector<sf::IntRect>& posSprites, const sf::Vector2f& tamanhoSprite, const int qps)
: resolucaoSistema(resolucaoSistema), quantidadeSprites(quantidadeSprites), posSprites(posSprites), sprite(textura), tamanhoSprite(tamanhoSprite), escala(resolucaoSistema.x/200.f), qps(qps) {
    limites[enums::direcao::esquerda] = resolucaoSistema.x*0.05f;
    limites[enums::direcao::direita] = resolucaoSistema.x*0.95f;
    velocidade = static_cast<float>(resolucaoSistema.x/qps);
    if(!textura.loadFromFile(caminhoTextura)) erroArquivo(caminhoTextura.string());
    sprite.setTexture(textura);
    sprite.setTextureRect(posSprites[0]);
    sprite.setOrigin(sf::Vector2f({tamanhoSprite.x/2.f, tamanhoSprite.y/2.f}));
    sprite.setPosition(sf::Vector2f({ resolucaoSistema.x/2.f - escala, resolucaoSistema.y*0.9f }));
    sprite.setScale(sf::Vector2f({escala, escala}));

    balaCooldown.start();
}

void jogador::atualizarBalas() {
    for(auto& bala: balas) {
        bala.mover();
    }
}

void jogador::mover(const enums::direcao dir) {
    switch(dir) {
        case enums::direcao::direita:
            if(sprite.getPosition().x < limites[enums::direcao::direita]) sprite.move(sf::Vector2f({velocidade, 0.f}));
            break;
        case enums::direcao::esquerda:
            if(sprite.getPosition().x > limites[enums::direcao::esquerda]) sprite.move(sf::Vector2f({-velocidade, 0.f}));
            break;
    }
}

void jogador::atirar() {
    if(balaCooldown.getElapsedTime().asSeconds() > 0.5f) {
        balaCooldown.restart();
        balas.emplace_back(sprite.getPosition(), escala, qps);
    }
}

void jogador::morte(const std::optional<std::reference_wrapper<janela>>& janela) {
    janela->get().setTravar();
    spriteAtual = 1;
    contadorTrocas = 0;
    sprite.setTextureRect(posSprites[spriteAtual]);
}

void jogador::calcularColisao(gerenciadorInimigos& gerenciadorInimigos, janela& janela) {
    auto it = balas.begin();
    while (it != balas.end()) {
        bool colisaoDetectada = false;

        for (int linha = 4; linha >= 0; --linha) {
            for (int coluna = 0; coluna < 11; ++coluna) {
                auto& inimigo = gerenciadorInimigos.getMapa()[linha][coluna];


                // Verifica se o inimigo está vivo
                if (inimigo.getEstado() == enums::condicao::vivo) {

                    // Verifica colisão
                    if (inimigo.checarColisao(*it)) {
                        inimigo.setEstado(enums::condicao::morrendo);
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

void jogador::atualizarAnimacaoMorte(janela& janela) {
    if (!animando) return;

    spriteAtual = (spriteAtual == 1 ? 2 : 1);
    sprite.setTextureRect(posSprites[spriteAtual]);
    ++contadorTrocas;

    if (contadorTrocas >= 20) {
        animando = false;
        janela.perdeuJogo();
    }
}

void jogador::restaurarJogador() {
    sprite.setPosition(sf::Vector2f({ resolucaoSistema.x/2.f - escala, resolucaoSistema.y*0.9f }));
}

std::vector<bala> jogador::getBalas() const& {
    return balas;
}

sf::Vector2f jogador::getPosition() const& {
    return sprite.getPosition();
}

sf::Sprite jogador::getSprite() const& {
    return sprite;
}

bala::bala(const sf::Vector2f &posicao, const float escala, const int qps) : posicao(posicao), escala(escala), qps(qps) {
    velocidade = -qps/15.f;
    forma.setPosition(sf::Vector2f(posicao.x, posicao.y*0.9f));
    forma.setSize(sf::Vector2f(1.f * escala, 4.f * escala));
}

sf::FloatRect bala::getRectBala() const& {
    return sf::FloatRect(forma.getPosition(), forma.getSize());
}

sf::RectangleShape bala::getForma() const& {
    return forma;
}

sf::Vector2f bala::getPosition() const& {
    return forma.getPosition();
}

void jogador::removerBalasForaDaTela() {
    auto it = balas.begin();
    while (it != balas.end()) {
        if (it->getPosition().y + it->getRectBala().size.y < 0.f ) {
            it = balas.erase(it);
        } else {
            ++it;
        }
    }
}

void bala::mover() {
    forma.move(sf::Vector2f(0.f, velocidade));
}
