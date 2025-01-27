#include <inimigo.hpp>
#include <erroManuseio.hpp>
#include <enums.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <filesystem>

alien::alien(const enums::tipo tipo, const std::array<sf::Vector2f, 3> &posSprites, const sf::Vector2f &tamanhoSprite) : tipo(tipo), posSprites(posSprites), tamanhoSprite(tamanhoSprite) {}