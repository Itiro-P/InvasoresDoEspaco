#include <jogador.hpp>
#include <erroManuseio.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <janela.hpp>
#include <enums.hpp>
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
}

sf::Vector2f jogador::getPosicao() const& {
    return sprite.getPosition();
}

sf::Sprite jogador::getSprite() const& {
    return sprite;
}