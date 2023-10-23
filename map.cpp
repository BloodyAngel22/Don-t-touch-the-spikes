#include "map.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cstdlib>
#include <ctime>

sf::RectangleShape curBlock_sprite;
int random_block = 0;

Map::Map(){
  srand(time(0));
  random_block = rand() % 4;

  createMap();
}

void Map::createMap(){
  srand(time(0));
  spikes.loadFromFile("image/spikes.png");
  blocks_texture.loadFromFile("image/blocks.png");
  /* Hero hero; */
  for (int i = 0; i < 18; i++){
    for (int j = 0; j < map[i].size(); j++){
      if (map[i][j] == 'x'){
        sf::RectangleShape block;
        block.setSize({60,60});
        /* block.setFillColor(sf::Color::Black); */
        block.setTexture(&blocks_texture);
        block.setTextureRect(sf::IntRect(64 * random_block, 0, 64, 64));
        block.setPosition(j * block.getSize().x, i * block.getSize().y);
        blocks.push_back(block);
      }
      if (map[i][j] == '^'){
        sf::RectangleShape thorn;
        thorn.setSize({60,60});
        /* thorn.setFillColor(sf::Color::Cyan); */
        thorn.setTexture(&spikes);
        thorn.setTextureRect(sf::IntRect(0, 0, 16, 16));
        thorn.setPosition(j * thorn.getSize().x, i * thorn.getSize().y);
        thorns.push_back(thorn);
      }
      if (map[i][j] == '|'){
        sf::RectangleShape thorn;
        thorn.setSize({60,60});
        /* thorn.setFillColor(sf::Color::Cyan); */
        thorn.setTexture(&spikes);
        thorn.setTextureRect(sf::IntRect(32, 0, 16, 16));
        thorn.setPosition(j * thorn.getSize().x, i * thorn.getSize().y);
        thorns.push_back(thorn);
      }
    }
  }
  for (int i = 2; i <= 15; i++){
    l_rand.push_back(i);
    r_rand.push_back(i);
  }
  for (int i = l_rand.size() - 1; i>= 1; i--){
    int j = rand() % (i+1);
    int tmp = l_rand[j];
    l_rand[j] = l_rand[i];
    l_rand[i] = tmp;
  }
  for (int i = r_rand.size() - 1; i>= 1; i--){
    int j = rand() % (i+1);
    int tmp = r_rand[j];
    r_rand[j] = r_rand[i];
    r_rand[i] = tmp;
  }
}

void Map::drawMap(sf::RenderWindow& window){
  for (int i = 0; i < blocks.size(); i++){
    window.draw(blocks[i]);
  }
  for (int i = 0; i < thorns.size(); i++){
    window.draw(thorns[i]);
  }
}

int cur_left_thorns = 0;
int cur_right_thorns = 0;
int change = 0;

void Map::changeMap(Hero& hero){
  curThorns(hero);
  for (int i = 0; i < 18; i++)
    for (int j = 0; j < map[i].size(); j++){
      if (map[change][j] == 'l'){
        if (cur_left_thorns > 0){
          cur_left_thorns--;
          map[change][j] = '>';
          sf::RectangleShape thorn;
          thorn.setSize({60,60});
          /* thorn.setFillColor(sf::Color::Yellow); */
          thorn.setTexture(&spikes);
          thorn.setTextureRect(sf::IntRect(16, 0, 16, 16));
          thorn.setPosition(j * thorn.getSize().x, change * thorn.getSize().y);
          /* std::cout << j * thorn.getSize().x << " " << i * thorn.getSize().y << std::endl; */
          thorns.push_back(thorn);
        }
      }
      if (map[change][j] == 'r'){
        if (cur_right_thorns > 0){
          cur_right_thorns--;
          map[change][j] = '<';
          sf::RectangleShape thorn;
          thorn.setSize({60,60});
          /* thorn.setFillColor(sf::Color::Yellow); */
          thorn.setTexture(&spikes);
          thorn.setTextureRect(sf::IntRect(48, 0, 16, 16));
          thorn.setPosition(j * thorn.getSize().x, change * thorn.getSize().y);
          /* std::cout << j * thorn.getSize().x << " " << i * thorn.getSize().y << std::endl; */
          thorns.push_back(thorn);
        }
      }
    }

}

void Map::curThorns(Hero& hero){
  int thorns_left[12] = { 5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115};
  int thorns_right[12] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
  for (int i = 0; i < 12; i++){
    if (hero.getScore() == thorns_left[i]){
      cur_left_thorns++;
      change = l_rand.at(l_rand.size()-1);
      l_rand.pop_back();
      /* std::cout << cur_left_thorns << std::endl; */
    }
    if (hero.getScore() == thorns_right[i]){
      cur_right_thorns++;
      change = r_rand.at(r_rand.size()-1);
      r_rand.pop_back();
    }
  }
}
