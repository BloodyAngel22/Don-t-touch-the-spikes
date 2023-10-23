#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#ifndef GAME_H
#define GAME_H
/* #include "include.h" */
#include "hero.h"

class Game{
  public:
    Game();
    int getWidth() { return width_; }
    int getHeight() {return height_; }
    void counterGame(Hero& hero, sf::RenderWindow& window);
    sf::Color getColor();
    const int FPS = 120;
  private:
    sf::CircleShape circle;
    int width_ = 1920;
    int height_ = 1080;
    void createColors();
    void setParameters();
    void randColor();
    sf::Color cur_color;
    std::vector <sf::Color> array_colors;
    sf::Font font;
    sf::Text hero_score_text;
};
#endif

