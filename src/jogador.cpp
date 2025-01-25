#include <jogador.hpp>
#include <erroManuseio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

jogador::jogador(const sf::Vector2u& resolucaoSistema, const std::filesystem::path& caminhoTextura, const int quantidadeSprites, const std::vector<sf::IntRect>& posSprites, const sf::Vector2f& tamanhoSprite)
: resolucaoSistema(resolucaoSistema), quantidadeQuadros(quantidadeQuadros), posSprites(posSprites), sprite(textura), tamanhoSprite(tamanhoSprite) {
    limites[esquerda] = static_cast<float>(resolucaoSistema.x*0.85+1);
    limites[direita] = static_cast<float>(resolucaoSistema.x*0.15);
    velocidade = static_cast<float>(resolucaoSistema.x/10);
    if(!textura.loadFromFile(caminhoTextura)) erroArquivo(caminhoTextura.string());
    sprite.setTexture(textura);
    sprite.setTextureRect(posSprites[0]);
    sprite.setOrigin(sf::Vector2f({tamanhoSprite.x/2.f, tamanhoSprite.y/2.f}));
    sprite.setPosition(sf::Vector2f({ resolucaoSistema.x/2.f, resolucaoSistema.y*0.9f }));
    sprite.setScale(sf::Vector2f({resolucaoSistema.x/150.f , resolucaoSistema.x/150.f}));
}

void jogador::mover(const direcao dir) {
    switch(dir) {
        case direita:
        if(sprite.getPosition().x < limites[direita]) sprite.move(sf::Vector2f({velocidade, 0.f}));
        break;
        case esquerda:
        if(sprite.getPosition().x > limites[esquerda]) sprite.move(sf::Vector2f({-velocidade, 0.f}));
        break;
    }
}

sf::Vector2f jogador::getPosicao() const& {
    return sprite.getPosition();
}

sf::Sprite jogador::getSprite() const& {
    return sprite;
}