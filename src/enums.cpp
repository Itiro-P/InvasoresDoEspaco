#include <enums.hpp>
#include <vector>
#include <SFML/Graphics.hpp>

alien::alien(const enums::tipo tipo, const std::vector<sf::Vector2f> &posSprites, const sf::Vector2f &tamanhoSprite) : tipo(tipo), posSprites(posSprites), tamanhoSprite(tamanhoSprite) {}