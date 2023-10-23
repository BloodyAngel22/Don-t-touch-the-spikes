#include "game.h"
#include "hero.h"
#include "map.h"

#include <SFML/Graphics/Texture.hpp>

bool press_flag = 1;

Hero::Hero(){
  Game g;
  Map m;
  if(!bird.loadFromFile("image/blue_bird.png"))
    std::cout << "bird doesn't load\n";
  bird_sprite.setTexture(bird);
  /* rect.setFillColor(sf::Color::Red); */
  for (int i = 0; i < 18; i++)
    for (int j = 0; j < m.map[i].size(); j++)
      if (m.map[i][j] == 'o')
        rect.setPosition(j * 60, i * 60);
  rect.setSize({60,60});
  float speed = 0.2;
  dx = speed * (g.FPS)/2, dy = speed * (g.FPS)/4;
  state = RIGHT;
}

void Hero::setPosition(int x, int y){
  rect.setPosition(x,y);
}

bool Hero::checkCollisionWithBlocks(){
  for (int i = 0; i < map.getBlocks().size(); i++){
    if (rect.getGlobalBounds().intersects(map.getBlocks()[i].getGlobalBounds()))
      return true;
  }
  return false;
}

bool Hero::checkCollisionWithThorns(){
  for (int i = 0; i < map.getThorns().size(); i++){
    if (rect.getGlobalBounds().intersects(map.getThorns()[i].getGlobalBounds()))
      return true;
  }
  return false;
}

bool isJumping = false;
bool isFalling = true;
int cur_height = 0;

void Hero::logic(sf::RenderWindow& window){
  update(window);
  jump();
  fall();
  const int shift = 15;
  if (state == RIGHT)
    bird_sprite.setPosition(rect.getPosition().x - shift, rect.getPosition().y - shift);
  if (state == LEFT)
    bird_sprite.setPosition(rect.getPosition().x + shift + rect.getSize().x, rect.getPosition().y - shift);
}

void Hero::update(sf::RenderWindow& window){
  bool block_collision = checkCollisionWithBlocks();
  bool thorn_collision = checkCollisionWithThorns();
  if (state == LEFT){
    rect.move({-dx, 0});
  }
  if (state == RIGHT){
    rect.move({dx, 0});
  }
  if (block_collision){
    float coef = dx * 2;
    if (state == RIGHT){
      bird_sprite.setScale(-1.f, 1.f);
      state = LEFT;
      rect.move({-coef, 0});
    }
    else if (state == LEFT) {
      state = RIGHT;
      bird_sprite.setScale(1.f, 1.f);
      rect.move({coef, 0});
    }
    score++;
    map.changeMap(hero);
  }
  if (thorn_collision)
    window.close();
  
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping && press_flag){
    isJumping = true;
    press_flag = 0;
  }
}

void Hero::jump(){
  if (isJumping) {
    rect.move({0, -dy});
    cur_height++;
    if (jump_height == cur_height){
      isJumping = false;
      cur_height = 0;
    }
  }
}

void Hero::fall(){
  if (!checkCollisionWithBlocks() && !isJumping){
    rect.move({0, dy});
  }
}
