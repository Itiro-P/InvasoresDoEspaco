#include <gerenciadorProjeteis.hpp>

void GerenciadorProjeteis::atirarJogador(const sf::Vector2f &posicao) {
    balasJogador.emplace_back(posicao, velocidade, escala);
}

void GerenciadorProjeteis::atirarAlien(const Tipo tipo, const std::array<sf::IntRect, 3> &posSprites, const sf::Texture &textura, const sf::Vector2f &posicao) {
    balasAlien.emplace_back(tipo, posSprites, textura, posicao, velocidade, escala);
}

void GerenciadorProjeteis::atualizarProjeteis() {
    // Atualiza as posições
    for(auto &bala: balasJogador) bala.mover();
    for(auto &bala: balasAlien) bala.mover();

    // Agora remove todas as balas fora da tela
    balasAlien.remove_if([this](BalaAlien &bala) { return bala.getRemover() || bala.getPosicao().y > resolucaoSistema.y; });
    balasJogador.remove_if([](BalaJogador &bala) { return bala.getRemover() || bala.getPosicao().y < 0.f; });
}