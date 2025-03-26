#include <recursoManager.hpp>

RecursoManager::RecursoManager() {
    limitesTela  = std::array{resolucaoSistema.x*0.05f, resolucaoSistema.x*0.95f};
    escala = resolucaoSistema.x/200.f;
    posicaoInicialJogador = sf::Vector2f{resolucaoSistema.x/2.f - escala, resolucaoSistema.y*0.9f};
    velocidadeBalas = qps/15.f;
    velocidade = static_cast<float>(resolucaoSistema.x/qps);
}
