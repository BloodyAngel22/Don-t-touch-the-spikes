#ifndef HERO_H
#define HERO_H 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

extern bool press_flag;

enum STATES{
  LEFT = 0,
  RIGHT = 1
};

class Hero{
  public:
    Hero();
    void logic(sf::RenderWindow& window);
    void setPosition(int x, int y);
    sf::RectangleShape getRect() { return rect; }
    int getScore() {return score; }
    sf::Sprite getSprite() {return bird_sprite;}
  private:
    sf::Texture bird;
    sf::RectangleShape rect;
    sf::Sprite bird_sprite;
    bool checkCollisionWithBlocks();
    bool checkCollisionWithThorns();
    void update(sf::RenderWindow& window);
    void jump();
    void fall();
    float dx, dy;
    int jump_height = 30;
    int state;
    int score = 0;
};

extern Hero hero;
#endif

