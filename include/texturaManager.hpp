#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <filesystem>

// NamesSpace com diretórios
namespace dir {
    const std::filesystem::path CaminhoIcone = "misc/icone.png";
    const std::filesystem::path CaminhoSprites = "misc/sprites.png";
    const std::filesystem::path CaminhoFonte = "misc/PixelifySans.ttf";
}

// Armazena textura e outros arquivos gráficos
class TexturaManager {
    TexturaManager() = default;
public:
    static sf::Texture& getTextura(const std::filesystem::path& caminho) {
        static std::unordered_map<std::string, sf::Texture> texturas;
            auto it = texturas.find(caminho.string());
            if (it == texturas.end()) {
                sf::Texture tex;
                if (!tex.loadFromFile(caminho)) {
                throw std::runtime_error("Falha ao carregar textura!");
            }
            texturas[caminho] = tex;
        }
        return texturas.at(caminho);
    }
};