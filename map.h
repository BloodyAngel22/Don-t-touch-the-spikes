#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <vector>

#ifndef MAP_H
#define MAP_H

#include "hero.h"

class Map{
  private:
    std::vector<sf::RectangleShape> blocks;
    std::vector<sf::RectangleShape> thorns;
    std::vector<sf::Sprite> block_sprites;
    std::vector <int> l_rand;
    std::vector <int> r_rand;
    sf::Texture spikes;
    sf::Texture blocks_texture;
    void createMap();
  public:
    std::string map[18] = {
      "      xxxxxxxxxxxxxxxxxxxx    ",
      "      x||||||||||||||||||x    ",
      "      xl                rx    ",
      "      xl                rx    ",
      "      xl                rx    ",
      "      xl                rx    ",
      "      xl                rx    ",
      "      xl                rx    ",
      "      xl     o          rx    ",
      "      xl                rx    ",
      "      xl                rx    ",
      "      xl                rx    ",
      "      xl                rx    ",
      "      xl                rx    ",
      "      xl                rx    ",
      "      xl                rx    ",
      "      x^^^^^^^^^^^^^^^^^^x    ",
      "      xxxxxxxxxxxxxxxxxxxx    "
    };
    Map();
    std::vector<sf::RectangleShape> getBlocks() {return blocks; }
    std::vector<sf::RectangleShape> getThorns() {return thorns; }
    void drawMap(sf::RenderWindow& window);
    void changeMap(Hero& hero);
    void curThorns(Hero& hero);
};

extern Map map;
#endif

