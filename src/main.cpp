#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <jogador.hpp>
#include <janela.hpp>
#include <inimigo.hpp>

int main() {

    std::filesystem::path caminhoIcone = "misc/icone.png";
    std::filesystem::path caminhoSprites = "misc/sprites.png";
    std::filesystem::path caminhoFonte = "misc/PixelifySans.ttf";

    sf::Vector2u resolucao(1280u, 720u);
    janela janela(resolucao, caminhoIcone, caminhoFonte);
    while(janela.getEstado()) {
        janela.eventos();
        janela.desenhar();
    }
    return 0;
}