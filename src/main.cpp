#include <interface.hpp>
#include <projetil.hpp>
#include <erroManuseio.hpp>
#include <recursoManager.hpp>
#include <gerenciadorProjeteis.hpp>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

int main() {
    RecursoManager recursoManager;
    GerenciadorAliens gerenciadorAliens(recursoManager);
    GerenciadorProjeteis gerenciadorProjeteis(recursoManager.getEscala(), recursoManager.getVelocidadeBalas(), recursoManager.getResolucaoSistema());
    Jogador jogador(recursoManager.getPosSpritesJogador()[0], recursoManager.getPosicaoInicialJogador(), recursoManager.getTamanhoSprite(), recursoManager.getEscala(), recursoManager.getVelocidade());
    EstadoJogador estadoJogador;

    Interface interface(recursoManager, gerenciadorAliens, gerenciadorProjeteis, jogador, estadoJogador);

    while(interface.getEstado()) {
        interface.atualizarProjeteis();
        interface.atualizarColisoes();
        interface.eventos();
        interface.desenhar();
    }
    return 0;
}