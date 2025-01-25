#include <jogador.hpp>
#include <erroManuseio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

jogador::jogador(const sf::Vector2u& resolucaoSistema, const std::filesystem::path& caminhoTextura, const int quantidadeQuadros, const std::vector<sf::Vector2f>& posQuadros, const sf::Vector2u& tamanhoSprite)
: resolucaoSistema(resolucaoSistema), quantidadeQuadros(quantidadeQuadros), posQuadros(posQuadros), sprite(textura), tamanhoSprite(tamanhoSprite) {
    limites[esquerda] = static_cast<float>(resolucaoSistema.x*0.85);
    limites[direita] = static_cast<float>(resolucaoSistema.x*0.15);
    velocidade = static_cast<float>(resolucaoSistema.x/100);
    if(!textura.loadFromFile(caminhoTextura)) erroArquivo(caminhoTextura.string());
    sprite.setOrigin(sf::Vector2f({tamanhoSprite.x/2.f, tamanhoSprite.y/2.f}));
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