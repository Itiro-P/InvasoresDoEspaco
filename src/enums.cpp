#include <enums.hpp>
#include <vector>
#include <SFML/Graphics.hpp>

alien::alien(const enums::tipo tipo, const std::array<sf::Vector2f, 3> &posSprites, const sf::Vector2f &tamanhoSprite) : tipo(tipo), posSprites(posSprites), tamanhoSprite(tamanhoSprite) {}